#ifndef S_MOVEMENT_H
#define S_MOVEMENT_H

#include "s_base.h"

enum class Axis { x, y };

class Map;

class S_Movement : public S_Base {
public:
    S_Movement(SystemManager* systemManager);
    ~S_Movement();

    void update(float dt);
    void handleEvent(const EntityId &entity, const EntityEvent &event);
    void notify(const Message &message);

    void setMap(Map* gameMap);

private:
    Map* mGameMap;

    void stopEntity(const EntityId& entity, const Axis& axis);
    void setDirection(const EntityId& entity, const Direction& dir);
    const sf::Vector2f& getTileFriction(unsigned int x, unsigned int y, unsigned int elevation);
    void movementStep(float dt, C_Movable* movable, C_Position* position);
};

#endif // S_MOVEMENT_H
