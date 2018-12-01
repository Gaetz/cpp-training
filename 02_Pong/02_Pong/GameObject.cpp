#include "GameObject.h"



GameObject::GameObject(): position_(Vector2())
{
}

GameObject::GameObject(Vector2 position): position_(position)
{
}


GameObject::~GameObject()
{
}

Vector2 GameObject::position() const
{
	return position_;
}

Vector2 & GameObject::rPosition()
{
	return position_;
}

void GameObject::setPosition(const Vector2 & v)
{
	position_.setX(v.x());
	position_.setY(v.y());
}
