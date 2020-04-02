#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"

class Enemy : public Character
{
public:
    Enemy(EntityManager* entityManager);
    ~Enemy();

    void onEntityCollision(EntityBase* collider, bool attack);
    void update(float dt);
private:
    sf::Vector2f mDestination;
    bool mHasDestination;
};

#endif // ENEMY_H
