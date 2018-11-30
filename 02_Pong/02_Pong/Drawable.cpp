#include "Drawable.h"

Drawable::Drawable()
{
	_position = Vector2(0, 0);
}

Drawable::Drawable(const Vector2 & position): _position(position)
{
}

Drawable::~Drawable()
{
}

void Drawable::setPosition(Vector2 position)
{
	_position.setX(position.x());
	_position.setY(position.y());
}
