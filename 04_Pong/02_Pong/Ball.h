#pragma once
#include "DrawableCircle.h"
#include "GameObject.h"
#include "Paddle.h"

#include <SDL.h>
#include <memory>

class Ball: public GameObject
{
public:
	Ball();
	Ball(const Vector2& position_, const Vector2& speed_, SDL_Renderer& renderer_, std::shared_ptr<Paddle> leftPaddle_, std::shared_ptr<Paddle> rightPaddle_);
	virtual ~Ball();

	void update(float dt_);
	void draw(SDL_Renderer& renderer_);

	void set_speed(const Vector2& speed_);

private:
	DrawableCircle graphics;
	Vector2 speed;
	std::shared_ptr<Paddle> left_paddle;
	std::shared_ptr<Paddle> right_paddle;

	void v_bounce();
	void h_bounce(bool on_player);
};

