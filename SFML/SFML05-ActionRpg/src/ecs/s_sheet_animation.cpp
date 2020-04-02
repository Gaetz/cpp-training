#include "s_sheet_animation.h"
#include "../core/system_manager.h"

S_SheetAnimation::S_SheetAnimation(SystemManager* systemManager) : S_Base(System::SheetAnimation, systemManager)
{
    Bitmask req;
    req.turnOnBit((unsigned int)Component::SpriteSheet);
    req.turnOnBit((unsigned int)Component::State);
    mRequiredComponents.push_back(req);

    mSystemManager->getMessageHandler()->subscribe(EntityMessage::State_Changed,this);
}

S_SheetAnimation::~S_SheetAnimation(){}

void S_SheetAnimation::update(float dt)
{
    EntityManager* entities = mSystemManager->getEntityManager();
    for(auto &entity : mEntities){
        C_SpriteSheet* sheet = entities->getComponent<C_SpriteSheet>(entity, Component::SpriteSheet);
        C_State* state = entities->getComponent<C_State>(entity, Component::State);

        sheet->getSpriteSheet()->update(dt);

        const std::string& animName = sheet->getSpriteSheet()->getCurrentAnim()->getName();
        if(animName == "Attack"){
            if(!sheet->getSpriteSheet()->getCurrentAnim()->isPlaying()) {
                Message message((MessageType)EntityMessage::Switch_State);
                message.mReceiver = entity;
                message.mInt = (int)EntityState::Idle;
                mSystemManager->getMessageHandler()->dispatch(message);
            } else if(sheet->getSpriteSheet()->getCurrentAnim()->isInAction()) {
                Message message((MessageType)EntityMessage::Attack_Action);
                message.mSender = entity;
                mSystemManager->getMessageHandler()->dispatch(message);
            }
        } else if(animName == "Death" && !sheet->getSpriteSheet()->getCurrentAnim()->isPlaying()) {
            Message message((MessageType)EntityMessage::Dead);
            message.mReceiver = entity;
            mSystemManager->getMessageHandler()->dispatch(message);
        }
    }
}

void S_SheetAnimation::handleEvent(const EntityId& entity, const EntityEvent& event) {}

void S_SheetAnimation::notify(const Message& message)
{
    if(hasEntity(message.mReceiver)){
        EntityMessage m = (EntityMessage)message.mType;
        switch(m){
        case EntityMessage::State_Changed:
            {
                EntityState s = (EntityState)message.mInt;
                switch(s){
                case EntityState::Idle:
                    changeAnimation(message.mReceiver,"Idle", true, true);
                    break;
                case EntityState::Walking:
                    changeAnimation(message.mReceiver,"Walk", true, true);
                    break;
                case EntityState::Attacking:
                    changeAnimation(message.mReceiver,"Attack", true, false);
                    break;
                case EntityState::Hurt: break;
                case EntityState::Dying:
                    changeAnimation(message.mReceiver,"Death", true, false);
                    break;
                default: break;
                }
            }
            break;
        default: break;
        }
    }
}

void S_SheetAnimation::changeAnimation(const EntityId& entity, const std::string& anim, bool play, bool loop)
{
    C_SpriteSheet* sheet = mSystemManager->getEntityManager()->getComponent<C_SpriteSheet>(entity, Component::SpriteSheet);
    sheet->getSpriteSheet()->setAnimation(anim, play, loop);
}
