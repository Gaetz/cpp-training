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
	int radius = graphics._radius();
	position += (speed * dt);
	graphics.s_position(position);
	// Bounces
	// - Out of screen
	if (position._y() < 0) {
		v_bounce();
		position.s_y(0);
	}
	else if (position._y() + radius > SCREEN_HEIGHT) {
		v_bounce();
		position.s_y(static_cast<float>(SCREEN_HEIGHT - radius));
	}
	// On paddles
	if (position._x() <= left_paddle->_width() + radius) {
		float leftPaddleY = left_paddle->_position()._y();
		if (position._y() >= leftPaddleY &&
			position._y() <= leftPaddleY + left_paddle->_height())
		{
			h_bounce();
			position.s_x(static_cast<float>(left_paddle->_width() + radius));
		}
	}
	if (position._x() >= right_paddle->_position()._x() - radius) {
		float rightPaddleY = right_paddle->_position()._y();
		if (position._y() >= rightPaddleY &&
			position._y() <= rightPaddleY + right_paddle->_height())
		{
			h_bounce();
			position.s_x(static_cast<float>(right_paddle->_position()._x() - radius));
		}
	}
}

void Ball::v_bounce()
{
	speed.s_y(-speed._y());
}

void Ball::h_bounce()
{
	speed.s_x(-speed._x());
}

void Ball::draw(SDL_Renderer& renderer) {
	graphics.draw(renderer);
}

void Ball::s_speed(const Vector2 & speed_)
{
	speed.s_x(speed_._x());
	speed.s_y(speed_._y());
}
