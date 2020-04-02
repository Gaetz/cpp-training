#ifndef CHARACTER_H
#define CHARACTER_H

#include "EntityBase.h"
#include "SpriteSheet.h"

class Character : public EntityBase
{
friend class EntityManager;
public:
    Character(EntityManager* entityManager);
    virtual ~Character();

    void move(const Direction& direction);

    void jump();
    void attack();
    void getHurt(const int& damage);

    void load(const std::string& path);

    virtual void onEntityCollision(EntityBase* collider, bool attack) = 0;

    virtual void update(float dt);
    void draw(sf::RenderWindow* window);

protected:
    SpriteSheet mSpriteSheet;
    float mJumpVelocity;
    int mHp;
    sf::FloatRect mAttackAABB;
    sf::Vector2f mAttackAABBoffset;

    void updateAttackAABB();
    void animate();
};
#endif // CHARACTER_H
