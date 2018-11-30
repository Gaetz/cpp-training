#include "Ball.h"

Ball::Ball()
{
}

Ball::Ball(Vector2 & position, Vector2 & speed, SDL_Renderer& renderer): DrawableCircle(position, 10, Color(255, 255, 255, 255), renderer), _speed(speed)
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
	if (_position.x() + _radius > 640.f) {
		hBounce();
		_position.setX(640.f - _radius);
	}
	if (_position.y() < 0) {
		vBounce();
		_position.setY(0);
	}
	if (_position.y() + _radius > 480.f) {
		vBounce();
		_position.setY(480.f - _radius);
	}
}

void Ball::vBounce()
{
	_speed.setY(-_speed.y());
}

void Ball::hBounce()
{
	_speed.setX(-_speed.x());
}
