#include "Ball.h"

Ball::Ball()
{
}

Ball::Ball(Vector2 & position, Vector2 & speed, SDL_Renderer& renderer, std::shared_ptr<Paddle> leftPaddle) : GameObject(position), speed_(speed), leftPaddle_(leftPaddle)
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
	// - Out of screen
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
	// On paddles
	if (position_.x() <= leftPaddle_->width() + radius) {
		float leftPaddleY = leftPaddle_->position().y();
		if (position_.y() >= leftPaddleY &&
			position_.y() <= leftPaddleY + leftPaddle_->height()) {
			hBounce();
		}
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

void Ball::setSpeed(const Vector2 & speed)
{
	speed_.setX(speed.x());
	speed_.setY(speed.y());
}
