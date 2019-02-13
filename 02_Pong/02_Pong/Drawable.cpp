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

void Drawable::set_position(const Vector2& position_)
{
	position.set_x(position_.get_x());
	position.set_y(position_.get_y());
}
