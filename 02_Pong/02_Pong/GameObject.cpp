#include "GameObject.h"



GameObject::GameObject(): position(Vector2())
{
}

GameObject::GameObject(const Vector2& position_): position(position_)
{
}


GameObject::~GameObject()
{
}

Vector2 GameObject::get_position() const
{
	return position;
}

Vector2 & GameObject::r_position()
{
	return position;
}

void GameObject::set_position(const Vector2 & v)
{
	position.set_x(v.get_x());
	position.set_y(v.get_y());
}
