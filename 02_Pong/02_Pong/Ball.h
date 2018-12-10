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
	Ball(Vector2& position_, Vector2& speed_, SDL_Renderer& renderer_, std::shared_ptr<Paddle> leftPaddle);
	virtual ~Ball();

	void update(float dt_);
	void draw(SDL_Renderer& renderer_);

	void setSpeed(const Vector2& speed);

private:
	DrawableCircle graphics_;
	Vector2 speed_;
	void vBounce();
	void hBounce();
	std::shared_ptr<Paddle> leftPaddle_;
	std::shared_ptr<Paddle> rightPaddle_;
};

