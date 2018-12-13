#include "Paddle.h"
#include "Input.h"
#include <algorithm>
#include "Constants.h"

Paddle::Paddle()
{
}

Paddle::Paddle(const Vector2& position_, const Vector2& size_, SDL_Renderer& renderer_, bool is_player_):
	GameObject(position_), width(static_cast<int>(size_._x())), height(static_cast<int>(size_._y())), is_player(is_player_)
{
	graphics = DrawableRect(position_, static_cast<int>(size_._x()), static_cast<int>(size_._y()), Color(), renderer_);
}


Paddle::~Paddle()
{
}

void Paddle::update(float dt)
{
	if (is_player) {
		float y = Input::mouse_pos()._y() - height / 2;
		y = std::clamp<float>(y, 0, static_cast<float>(SCREEN_HEIGHT - height));
		position.s_y(y);
	}
	else {
		if (ball_y > position._y() + height * 3 / 4) {
			position.s_y(position._y() + OPPONENT_SPEED);
		}
		else if (ball_y < position._y() + height / 4) {
			position.s_y(position._y() - OPPONENT_SPEED);
		}
	}
	graphics.s_position(position);
}

void Paddle::draw(SDL_Renderer & renderer)
{
	graphics.draw(renderer);
}

int Paddle::_width() const
{
	return width;
}

int Paddle::_height() const
{
	return height;
}

void Paddle::s_ball_y(const float y_)
{
	ball_y = y_;
}
