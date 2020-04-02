//#include "Player.h"
//#include "../core/EntityManager.h"
//#include "../core/StateManager.h"

//Player::Player(EntityManager *entityManager) : Character(entityManager)
//{
//    load("player.char");
//    mType = EntityType::Player;

//    // Inputs
//    EventManager* events = mEntityManager->getContext()->mEventManager;
//    events->addCallback(StateType::Game, "Player_MoveRight", &Player::react, this);
//    events->addCallback(StateType::Game, "Player_MoveLeft", &Player::react, this);
//    events->addCallback(StateType::Game, "Player_Jump", &Player::react, this);
//    events->addCallback(StateType::Game, "Player_Attack", &Player::react, this);
//}

//Player::~Player()
//{
//    EventManager* events = mEntityManager->getContext()->mEventManager;
//    events->removeCallback(StateType::Game, "Player_MoveRight");
//    events->removeCallback(StateType::Game, "Player_MoveLeft");
//    events->removeCallback(StateType::Game, "Player_Jump");
//    events->removeCallback(StateType::Game, "Player_Attack");
//}


//void Player::react(EventDetails *details)
//{
//    if (details->mName == "Player_MoveLeft"){
//        Character::move(Direction::Left);
//    } else if (details->mName == "Player_MoveRight"){
//        Character::move(Direction::Right);
//    } else if (details->mName == "Player_Jump"){
//        Character::jump();
//    } else if (details->mName == "Player_Attack"){
//        Character::attack();
//    }
//}

//void Player::onEntityCollision(EntityBase *collider, bool attack)
//{
//    if(mState == EntityState::Dying)
//        return;
//    // Attack
//    if(attack) {
//        if(mState != EntityState::Attacking)
//            return;
//        if(!mSpriteSheet.getCurrentAnim()->isInAction())
//            return;
//        if(collider->getType() != EntityType::Enemy && collider->getType() != EntityType::Player)
//            return;
//        // Hit
//        Character* opponent = (Character*)collider;
//        opponent->getHurt(1);
//        // Knock back
//        if(mPosition.x > opponent->getPosition().x) {
//            opponent->addVelocity(-32, 0);
//        } else {
//            opponent->addVelocity(32, 0);
//        }
//    }
//    // Other behaviours
//    else {

//    }
//}
