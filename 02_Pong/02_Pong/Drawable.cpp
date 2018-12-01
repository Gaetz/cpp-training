#include "Drawable.h"

Drawable::Drawable()
{
	position_ = Vector2(0, 0);
}

Drawable::Drawable(const Vector2 & position): position_(position)
{
}

Drawable::~Drawable()
{
}

void Drawable::setPosition(Vector2 position)
{
	position_.setX(position.x());
	position_.setY(position.y());
}
