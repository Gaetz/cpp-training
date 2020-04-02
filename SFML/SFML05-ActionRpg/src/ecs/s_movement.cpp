#include "s_movement.h"
#include "../core/system_manager.h"
#include "../display/map.h"

S_Movement::S_Movement(SystemManager *systemManager) : S_Base(System::Movement, systemManager)
{
    Bitmask req;
    req.turnOnBit((unsigned int)Component::Position);
    req.turnOnBit((unsigned int)Component::Movable);
    mRequiredComponents.push_back(req);
    req.clear();
    mSystemManager->getMessageHandler()->subscribe(EntityMessage::Is_Moving, this);

    mGameMap = nullptr;
}

S_Movement::~S_Movement() {}

void S_Movement::update(float dt)
{
    if(!mGameMap)
        return;
    EntityManager* entities = mSystemManager->getEntityManager();
    for(auto &entity: mEntities) {
        C_Position* position = entities->getComponent<C_Position>(entity, Component::Position);
        C_Movable* movable = entities->getComponent<C_Movable>(entity, Component::Movable);
        movementStep(dt, movable, position);
        position->moveBy(movable->getVelocity() * dt);
    }
}

void S_Movement::movementStep(float dt, C_Movable *movable, C_Position *position)
{
    sf::Vector2f frictionCoefficient = getTileFriction(
                floor(position->getPosition().x / Sheet::TileSize),
                floor(position->getPosition().y / Sheet::TileSize),
                position->getElevation());
    sf::Vector2f friction(movable->getSpeed().x * frictionCoefficient.x, movable->getSpeed().y * frictionCoefficient.y);

    movable->addVelocity(movable->getAcceleration() * dt);
    movable->SetAcceleration(sf::Vector2f(0.f, 0.f));
    movable->applyFriction(friction * dt);

    // Normalize diagonal movement
    float magnitude = sqrt(movable->getVelocity().x * movable->getVelocity().x + movable->getVelocity().y * movable->getVelocity().y);
    if(magnitude <= movable->getMaxVelocity())
        return;
    float maxV = movable->getMaxVelocity();
    movable->SetVelocity(sf::Vector2f(movable->getVelocity().x / magnitude * maxV, movable->getVelocity().y / magnitude * maxV));
}

const sf::Vector2f& S_Movement::getTileFriction(unsigned int x, unsigned int y, unsigned int elevation) {
    Tile* t = nullptr;
    while(!t && elevation >= 0) {
        t = mGameMap->getTile(x, y, elevation);
        --elevation;
    }

    return t ? t->mProperties->mFriction : mGameMap->getDefaultTile()->mFriction;
}

void S_Movement::handleEvent(const EntityId &entity, const EntityEvent &event)
{
    switch(event) {
    case EntityEvent::Colliding_X:
        stopEntity(entity, Axis::x); break;
    case EntityEvent::Colliding_Y:
        stopEntity(entity, Axis::y); break;
    case EntityEvent::Moving_Left:
        setDirection(entity, Direction::Left); break;
    case EntityEvent::Moving_Right:
        setDirection(entity, Direction::Right); break;
    case EntityEvent::Moving_Up:
    {
        C_Movable* movable = mSystemManager->getEntityManager()->getComponent<C_Movable>(entity, Component::Movable);
        if(movable->getVelocity().x == 0) {
            setDirection(entity, Direction::Up);
        }
    }
        break;
    case EntityEvent::Moving_Down:
    {
        C_Movable* movable = mSystemManager->getEntityManager()->getComponent<C_Movable>(entity, Component::Movable);
        if(movable->getVelocity().x == 0) {
            setDirection(entity, Direction::Down);
        }
    }
        break;
    default:
        break;
    }
}

void S_Movement::notify(const Message &message)
{
    EntityManager* entityManager = mSystemManager->getEntityManager();
    EntityMessage m = (EntityMessage)message.mType;
    switch(m) {
    case EntityMessage::Is_Moving: {
        if(!hasEntity(message.mReceiver))
            return;
        C_Movable* movable = entityManager->getComponent<C_Movable>(message.mReceiver, Component::Movable);
        if(movable->getVelocity() != sf::Vector2f(0.f, 0.f))
            return;
        mSystemManager->addEvent(message.mReceiver, (EventId)EntityEvent::Became_Idle);
    }
        break;
    default:
        break;
    }
}

void S_Movement::stopEntity(const EntityId &entity, const Axis &axis)
{
    C_Movable* movable = mSystemManager->getEntityManager()->getComponent<C_Movable>(entity, Component::Movable);
    if(axis == Axis::x) {
        movable->SetVelocity(sf::Vector2f(0.f, movable->getVelocity().y));
    } else if(axis == Axis::y) {
        movable->SetVelocity(sf::Vector2f(movable->getVelocity().x, 0.f));
    }
}

void S_Movement::setDirection(const EntityId &entity, const Direction &dir)
{
    C_Movable* movable = mSystemManager->getEntityManager()->getComponent<C_Movable>(entity, Component::Movable);
    movable->SetDirection(dir);

    Message message((MessageType)EntityMessage::Direction_Changed);
    message.mReceiver = entity;
    message.mInt = (int)dir;
    mSystemManager->getMessageHandler()->dispatch(message);
}


void S_Movement::setMap(Map *gameMap)
{
    mGameMap = gameMap;
}
