#include "Ball.h"

Ball::Ball()
{
}

Ball::Ball(Vector2 & position, Vector2 & speed, SDL_Renderer& renderer): GameObject(position), speed_(speed)
{
	graphics_ = DrawableCircle(position, 10, Color(255, 255, 255, 255), renderer);
}

Ball::~Ball()
{
}

void Ball::update(float dt)
{
	int radius = graphics_.radius();
	position_ += (speed_ * dt);
	graphics_.setPosition(position_);
	// Bounces
	if (position_.x() < 0) {
		hBounce();
		position_.setX(0);
	}
	if (position_.x() + radius > 640.f) {
		hBounce();
		position_.setX(640.f - radius);
	}
	if (position_.y() < 0) {
		vBounce();
		position_.setY(0);
	}
	if (position_.y() + radius > 480.f) {
		vBounce();
		position_.setY(480.f - radius);
	}
}

void Ball::vBounce()
{
	speed_.setY(-speed_.y());
}

void Ball::hBounce()
{
	speed_.setX(-speed_.x());
}

void Ball::draw(SDL_Renderer& renderer) {
	graphics_.draw(renderer);
}