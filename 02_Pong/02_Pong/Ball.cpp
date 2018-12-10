#include "Ball.h"
#include "Constants.h"

Ball::Ball()
{
}

Ball::Ball(Vector2 & position, Vector2 & speed, SDL_Renderer& renderer, std::shared_ptr<Paddle> leftPaddle, std::shared_ptr<Paddle> rightPaddle) :
	GameObject(position), speed_(speed), leftPaddle_(leftPaddle), rightPaddle_(rightPaddle)
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
	if (position_.y() < 0) {
		vBounce();
		position_.setY(0);
	}
	else if (position_.y() + radius > SCREEN_HEIGHT) {
		vBounce();
		position_.setY(480.f - radius);
	}
	// On paddles
	if (position_.x() <= leftPaddle_->width() + radius) {
		float leftPaddleY = leftPaddle_->position().y();
		if (position_.y() >= leftPaddleY &&
			position_.y() <= leftPaddleY + leftPaddle_->height())
		{
			hBounce();
			position_.setX(static_cast<float>(leftPaddle_->width() + radius));
		}
	}
	if (position_.x() >= rightPaddle_->position().x() - radius) {
		float rightPaddleY = rightPaddle_->position().y();
		if (position_.y() >= rightPaddleY &&
			position_.y() <= rightPaddleY + rightPaddle_->height())
		{
			hBounce();
			position_.setX(static_cast<float>(rightPaddle_->position().x() - radius));
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
