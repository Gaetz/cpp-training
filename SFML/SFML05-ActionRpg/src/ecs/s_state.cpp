#include "s_state.h"
#include "../core/system_manager.h"

S_State::S_State(SystemManager *systemManager) : S_Base(System::State, systemManager)
{
    Bitmask req;
    req.turnOnBit((unsigned int)Component::State);
    mRequiredComponents.push_back(req);
    req.clear();

    mSystemManager->getMessageHandler()->subscribe(EntityMessage::Move, this);
    mSystemManager->getMessageHandler()->subscribe(EntityMessage::Switch_State, this);
}

S_State::~S_State() {}

void S_State::update(float dt) {
    EntityManager* entities = mSystemManager->getEntityManager();
    for(auto &entity : mEntities) {
        C_State* state = entities->getComponent<C_State>(entity, Component::State);
        if(state->getState() == EntityState::Walking) {
            Message message((MessageType)EntityMessage::Is_Moving);
            message.mReceiver = entity;
            mSystemManager->getMessageHandler()->dispatch(message);
        }
    }
}

void S_State::handleEvent(const EntityId &entity, const EntityEvent &event)
{
    switch (event) {
    case EntityEvent::Became_Idle:
        changeState(entity, EntityState::Idle, false);
        break;
    default:
        break;
    }
}

void S_State::notify(const Message &message)
{
    if(!hasEntity(message.mReceiver))
        return;
    EntityMessage m = (EntityMessage)message.mType;
    switch (m) {
    case EntityMessage::Move: {
        C_State* state = mSystemManager->getEntityManager()->getComponent<C_State>(message.mReceiver, Component::State);
        if(state->getState() == EntityState::Dying)
            return;
        EntityEvent e;
        if(message.mInt == (int)Direction::Up) {
            e = EntityEvent::Moving_Up;
        } else if(message.mInt == (int)Direction::Down) {
            e = EntityEvent::Moving_Down;
        } else if(message.mInt == (int)Direction::Left) {
            e = EntityEvent::Moving_Left;
        } else if(message.mInt == (int)Direction::Right) {
            e = EntityEvent::Moving_Right;
        }

        mSystemManager->addEvent(message.mReceiver, (EventId)e);
        changeState(message.mReceiver, EntityState::Walking, false);
    }
        break;
    case EntityMessage::Switch_State: {
        changeState(message.mReceiver, (EntityState)message.mInt, false);
    }
        break;
    default:
        break;
    }
}

void S_State::changeState(const EntityId &entity, const EntityState &state, const bool &force)
{
    EntityManager* entities = mSystemManager->getEntityManager();
    C_State* formerState = entities->getComponent<C_State>(entity, Component::State);
    if(!force && formerState->getState() == EntityState::Dying)
        return;
    formerState->setState(state);
    Message message((MessageType)EntityMessage::State_Changed);
    message.mReceiver = entity;
    message.mInt = (int)state;
    mSystemManager->getMessageHandler()->dispatch(message);
}
