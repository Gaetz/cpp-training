#ifndef C_POSITION_H
#define C_POSITION_H

#include <SFML/System/Vector2.hpp>
#include "c_base.h"

class C_Position: public C_Base {
public:
    C_Position(): C_Base(Component::Position), mElevation(0) {}
    ~C_Position() {}

    void readIn(std::stringstream& stream) {
        stream >> mPosition.x >> mPosition.y >> mElevation;
    }

    const sf::Vector2f& getPosition() { return mPosition; }
    const sf::Vector2f& getOldPosition() { return mPositionOld; }
    const unsigned int getElevation() { return mElevation; }

    void setPosition(float x, float y) {
        mPositionOld = mPosition;
        mPosition = sf::Vector2f(x, y);
    }

    void setPosition(const sf::Vector2f& position) {
        mPositionOld = mPosition;
        mPosition = position;
    }

    void setElevation(unsigned int elevation) {
        mElevation = elevation;
    }

    void moveBy(float x, float y) {
        mPositionOld = mPosition;
        mPosition += sf::Vector2f(x, y);
    }

    void moveBy(sf::Vector2f moveVector) {
        mPositionOld = mPosition;
        mPosition += moveVector;
    }

private:
    sf::Vector2f mPosition;
    sf::Vector2f mPositionOld;
    unsigned int mElevation;
};

#endif // C_POSITION_H
