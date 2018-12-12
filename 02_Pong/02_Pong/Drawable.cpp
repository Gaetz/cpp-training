#include "Drawable.h"

Drawable::Drawable()
{
	position = Vector2(0, 0);
}

Drawable::Drawable(const Vector2 & position_): position(position_)
{
}

Drawable::~Drawable()
{
}

void Drawable::s_position(const Vector2& position_)
{
	position.s_x(position_._x());
	position.s_y(position_._y());
}
