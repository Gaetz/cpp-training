#include "Ball.h"

Ball::Ball()
{
}

Ball::Ball(Vector2 & position, Vector2 & speed): DrawableCircle(position, 10, 0, Color(255, 0, 255, 255), true), _speed(speed)
{
}

Ball::~Ball()
{
}

void Ball::update(float dt)
{
	_position += (_speed * dt);
	if (_position.x() < 0) {
		hBounce();
		_position.setX(0);
	}
	if (_position.x() + _radius > 800) {
		hBounce();
		_position.setX(800.f - _radius);
	}
	if (_position.y() < 0) {
		vBounce();
		_position.setY(0);
	}
	if (_position.y() + _radius > 600) {
		vBounce();
		_position.setY(600.f - _radius);
	}
}

void Ball::vBounce()
{
	_speed.ry() = -_speed.y();
}

void Ball::hBounce()
{
	_speed.rx() = -_speed.x();
}
