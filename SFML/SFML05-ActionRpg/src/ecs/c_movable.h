#ifndef C_MOVABLE_H
#define C_MOVABLE_H

#include "c_base.h"
#include "../display/directions.h"
#include <SFML/System/Vector2.hpp>

class C_Movable: public C_Base {
public:
    C_Movable(): C_Base(Component::Movable), mVelocityMax(0.f), mDirection((Direction)0) {}

    void readIn(std::stringstream &stream)
    {
        stream >> mVelocityMax >> mSpeed.x >> mSpeed.y;
        unsigned int dir = 0;
        stream >> dir;
        mDirection = (Direction)dir;
    }

    const sf::Vector2f& getVelocity(){ return mVelocity; }
    float getMaxVelocity(){ return mVelocityMax; }
    const sf::Vector2f& getSpeed(){ return mSpeed; }
    const sf::Vector2f& getAcceleration(){ return mAcceleration; }
    Direction getDirection(){ return mDirection; }

    void SetVelocity(const sf::Vector2f& velocity){ mVelocity = velocity; }
    void SetMaxVelocity(float maxVelocity){ mVelocityMax = maxVelocity; }
    void SetSpeed(const sf::Vector2f& speed){ mSpeed = speed; }
    void SetAcceleration(const sf::Vector2f& acceleration){ mAcceleration = acceleration; }
    void SetDirection(const Direction& dir){ mDirection = dir; }

    void addVelocity(const sf::Vector2f& impulse)
    {
        mVelocity += impulse;
        if(std::abs(mVelocity.x) > mVelocityMax) {
            mVelocity.x = mVelocityMax * mVelocity.x / std::abs(mVelocity.x); // Max velocity with appropriate sign
        }
        if(std::abs(mVelocity.y) > mVelocityMax) {
            mVelocity.y = mVelocityMax * mVelocity.y / std::abs(mVelocity.y);
        }
    }

    void applyFriction(const sf::Vector2f& friction)
    {
        if(mVelocity.x != 0 && friction.x != 0) {
            if(std::abs(mVelocity.x) - std::abs(friction.x) < 0) {
                mVelocity.x = 0;
            } else {
                mVelocity.x += (mVelocity.x > 0 ? -friction.x : friction.x);
            }
        }
        if(mVelocity.y != 0 && friction.y != 0) {
            if(std::abs(mVelocity.y) - std::abs(friction.y) < 0) {
                mVelocity.y = 0;
            } else {
                mVelocity.y += (mVelocity.y > 0 ? -friction.y : friction.y);
            }
        }
    }

    void accelerate(const sf::Vector2f variation) {
        mAcceleration += variation;
    }

    void accelerate(float varX, float varY) {
        mAcceleration += sf::Vector2f(varX, varY);
    }

    void move(const Direction dir) {
        if(dir == Direction::Up) {
            mAcceleration.y = -mSpeed.y;
        } else if(dir == Direction::Down) {
            mAcceleration.y = mSpeed.y;
        } else if(dir == Direction::Left) {
            mAcceleration.x = -mSpeed.x;
        } else if(dir == Direction::Right) {
            mAcceleration.x = mSpeed.x;
        }
    }

private:
    sf::Vector2f mVelocity;
    float mVelocityMax;
    sf::Vector2f mSpeed;
    sf::Vector2f mAcceleration;
    Direction mDirection;
};
#endif // C_MOVABLE_H
