#include "s_control.h"
#include "../core/system_manager.h"

S_Control::S_Control(SystemManager* systemManager) : S_Base(System::Control, systemManager)
{
    Bitmask req;
    req.turnOnBit((unsigned int)Component::Position);
    req.turnOnBit((unsigned int)Component::Movable);
    req.turnOnBit((unsigned int)Component::Controller);
    mRequiredComponents.push_back(req);
    req.clear();
}

S_Control::~S_Control() {}

void S_Control::update(float dt){}

void S_Control::handleEvent(const EntityId& entity, const EntityEvent& event)
{
    switch(event){
    case EntityEvent::Moving_Left: moveEntity(entity, Direction::Left); break;
    case EntityEvent::Moving_Right: moveEntity(entity, Direction::Right); break;
    case EntityEvent::Moving_Up: moveEntity(entity, Direction::Up); break;
    case EntityEvent::Moving_Down: moveEntity(entity, Direction::Down); break;
    default: break;
    }
}

void S_Control::notify(const Message& message){}

void S_Control::moveEntity(const EntityId& entity, const Direction& dir)
{
    C_Movable* movable = mSystemManager->getEntityManager()->getComponent<C_Movable>(entity, Component::Movable);
    movable->move(dir);
}
