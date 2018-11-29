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
