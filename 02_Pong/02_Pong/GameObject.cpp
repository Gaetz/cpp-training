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

Vector2 GameObject::_position() const
{
	return position;
}

Vector2 & GameObject::r_position()
{
	return position;
}

void GameObject::s_position(const Vector2 & v)
{
	position.s_x(v._x());
	position.s_y(v._y());
}
