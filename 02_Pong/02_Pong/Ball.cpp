#include "Ball.h"
#include "Constants.h"

Ball::Ball()
{
}

Ball::Ball(const Vector2 & position_, const Vector2 & speed_, SDL_Renderer& renderer_, std::shared_ptr<Paddle> leftPaddle_, std::shared_ptr<Paddle> rightPaddle_) :
	GameObject(position_), speed(speed_), left_paddle(leftPaddle_), right_paddle(rightPaddle_)
{
	graphics = DrawableCircle(position, 10, Color(255, 255, 255, 255), renderer_);
}

Ball::~Ball()
{
}

void Ball::update(float dt)
{
	int radius = graphics.get_radius();
	position += (speed * dt);
	graphics.set_position(position);
	right_paddle->set_ball_y(position.get_y());
	// Bounces
	// - Out of screen
	if (position.get_y() < 0) {
		v_bounce();
		position.set_y(0);
	}
	else if (position.get_y() + radius > SCREEN_HEIGHT) {
		v_bounce();
		position.set_y(static_cast<float>(SCREEN_HEIGHT - radius));
	}
	// On paddles
	if (position.get_x() <= left_paddle->get_width() + radius) {
		float leftPaddleY = left_paddle->get_position().get_y();
		if (position.get_y() >= leftPaddleY &&
			position.get_y() <= leftPaddleY + left_paddle->get_height())
		{
			h_bounce(true);
			position.set_x(static_cast<float>(left_paddle->get_width() + radius));
		}
	}
	if (position.get_x() >= right_paddle->get_position().get_x() - radius) {
		float rightPaddleY = right_paddle->get_position().get_y();
		if (position.get_y() >= rightPaddleY &&
			position.get_y() <= rightPaddleY + right_paddle->get_height())
		{
			h_bounce(false);
			position.set_x(static_cast<float>(right_paddle->get_position().get_x() - radius));
		}
	}
}

void Ball::v_bounce()
{
	speed.set_y(-speed.get_y());
}

void Ball::h_bounce(bool on_player)
{
	speed.set_x(-speed.get_x());
	if (on_player) {
		float left_paddle_center = left_paddle->get_position().get_y() + left_paddle->get_height() / 2;
		speed.set_y((position.get_y() - left_paddle_center) / left_paddle->get_height() / 2 * BALL_SPEED.get_y() * PADDLE_BOUNCE_MULT);
	}
	else {
		float right_paddle_center = right_paddle->get_position().get_y() + right_paddle->get_height() / 2;
		speed.set_y((position.get_y() - right_paddle_center) / right_paddle->get_height() / 2 * BALL_SPEED.get_y() * PADDLE_BOUNCE_MULT);
	}
}

void Ball::draw(SDL_Renderer& renderer) {
	graphics.draw(renderer);
}

void Ball::set_speed(const Vector2 & speed_)
{
	speed.set_x(speed_.get_x());
	speed.set_y(speed_.get_y());
}
