//#include "Enemy.h"

//Enemy::Enemy(EntityManager *entityManager):
//    Character(entityManager),
//    mHasDestination(false)
//{
//    mType = EntityType::Enemy;
//}

//Enemy::~Enemy() {}

//void Enemy::onEntityCollision(EntityBase *collider, bool attack)
//{
//    if(mState == EntityState::Dying)
//        return;
//    if(attack)
//        return;
//    if(collider->getType() != EntityType::Player)
//        return;
//    // Attack when player is collided
//    Character* player = (Character*)collider;
//    setState(EntityState::Attacking);
//    player->getHurt(1);
//    // Knock back
//    if(mPosition.x > player->getPosition().x) {
//        player->addVelocity(-mSpeed.x, 0);
//        mSpriteSheet.setDirection(Direction::Left);
//    } else {
//        player->addVelocity(mSpeed.x, 0);
//        mSpriteSheet.setDirection(Direction::Right);
//    }
//}

//void Enemy::update(float dt)
//{
//    Character::update(dt);

//    if(mHasDestination) {
//        if(std::abs(mDestination.x - mPosition.x) < 16) {
//            mHasDestination = false;
//            return;
//        }
//        if(mDestination.x - mPosition.x > 0) {
//            move(Direction::Right);
//        } else {
//            move(Direction::Left);
//        }
//        if(mCollidingOnX) {
//            mHasDestination = false;
//        }
//        return;
//    }

//    int random = rand() % 1000 + 1;
//    if(random < 995) // 5 chances out of 1000 to move
//        return;
//    int newX = rand() %100 + 0; // Move of 200 px max
//    if(rand() % 2) {
//        newX = -newX;
//    }
//    mDestination.x = mPosition.x + newX;
//    if(mDestination.x < 0) {
//        mDestination.x = 0;
//    }
//    mHasDestination = true;
//}
