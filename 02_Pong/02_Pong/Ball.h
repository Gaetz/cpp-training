#pragma once
#include "DrawableCircle.h"
#include "GameObject.h"

#include <SDL.h>

class Ball: public GameObject
{
public:
	Ball();
	Ball(Vector2& position_, Vector2& speed_, SDL_Renderer& renderer_);
	virtual ~Ball();

	void update(float dt_);
	void draw(SDL_Renderer& renderer_);

private:
	DrawableCircle graphics_;
	Vector2 speed_;
	void vBounce();
	void hBounce();
};

