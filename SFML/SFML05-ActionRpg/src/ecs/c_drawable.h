#ifndef C_DRAWABLE_H
#define C_DRAWABLE_H

#include "c_base.h"
#include <SFML/Graphics.hpp>

class C_Drawable : public C_Base
{
public:
    C_Drawable(const Component& type) : C_Base(type) {}
    virtual ~C_Drawable() {}

    virtual void updatePosition(const sf::Vector2f& position) = 0;
    virtual const sf::Vector2u& getSize() = 0;
    virtual void draw(sf::RenderWindow* window) = 0;
};

#endif // C_DRAWABLE_H
