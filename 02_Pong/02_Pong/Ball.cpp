#include "Ball.h"

Ball::Ball()
{
}

Ball::Ball(Vector2 & position, Vector2 & speed, SDL_Renderer& renderer): GameObject(position), _speed(speed)
{
	_graphics = DrawableCircle(position, 10, Color(255, 255, 255, 255), renderer);
}

Ball::~Ball()
{
}

void Ball::update(float dt)
{
	int radius = _graphics.radius();
	_position += (_speed * dt);
	_graphics.setPosition(_position);
	if (_position.x() < 0) {
		hBounce();
		_position.setX(0);
	}
	if (_position.x() + radius > 640.f) {
		hBounce();
		_position.setX(640.f - radius);
	}
	if (_position.y() < 0) {
		vBounce();
		_position.setY(0);
	}
	if (_position.y() + radius > 480.f) {
		vBounce();
		_position.setY(480.f - radius);
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

void Ball::draw(SDL_Renderer& renderer) {
	_graphics.draw(renderer);
}