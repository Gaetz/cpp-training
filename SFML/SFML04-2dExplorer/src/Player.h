#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "EventManager.h"
#include "EntityManager.h"

class Player : public Character
{
public:
    Player(EntityManager* entityManager);
    ~Player();

    void onEntityCollision(EntityBase* collider, bool attack);
    void react(EventDetails* details);
};

#endif // PLAYER_H
