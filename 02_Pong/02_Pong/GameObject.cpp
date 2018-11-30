#include "GameObject.h"



GameObject::GameObject(): _position(Vector2())
{
}

GameObject::GameObject(Vector2 position): _position(position)
{
}


GameObject::~GameObject()
{
}

Vector2 GameObject::position() const
{
	return _position;
}

Vector2 & GameObject::rPosition()
{
	return _position;
}

void GameObject::setPosition(const Vector2 & v)
{
	_position.setX(v.x());
	_position.setY(v.y());
}
