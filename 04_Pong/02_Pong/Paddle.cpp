#include "Paddle.h"
#include <algorithm>
#include "Constants.h"

Paddle::Paddle()
{
}

Paddle::Paddle(const Vector2& position_, const Vector2& size_, SDL_Renderer& renderer_, bool is_player_):
	GameObject(position_), width(static_cast<int>(size_.get_x())), height(static_cast<int>(size_.get_y())), is_player(is_player_)
{
	graphics = DrawableRect(position_, static_cast<int>(size_.get_x()), static_cast<int>(size_.get_y()), Color(), renderer_);
}


Paddle::~Paddle()
{
}

void Paddle::update(float dt)
{
	if (is_player) {
		float y = Input::mouse_pos().get_y() - height / 2;
		y = std::clamp<float>(y, 0, SCREEN_HEIGHT - height);
		position.set_y(y);
	}
	else {
		if (ball_y > position.get_y() + height - DEAD_ZONE_HEIGHT) {
			position.set_y(position.get_y() + OPPONENT_SPEED);
		}
		else if (ball_y < position.get_y() + DEAD_ZONE_HEIGHT) {
			position.set_y(position.get_y() - OPPONENT_SPEED);
		}
	}
	graphics.set_position(position);
}

void Paddle::draw(SDL_Renderer & renderer)
{
	graphics.draw(renderer);
}

int Paddle::get_width() const
{
	return width;
}

int Paddle::get_height() const
{
	return height;
}

void Paddle::set_ball_y(const float y_)
{
	ball_y = y_;
}
