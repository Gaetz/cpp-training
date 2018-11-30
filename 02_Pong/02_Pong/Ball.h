#pragma once
#include "DrawableCircle.h"
#include <SDL.h>

class Ball :
	public DrawableCircle
{
public:
	Ball();
	Ball(Vector2& position, Vector2& speed, SDL_Renderer& renderer);
	virtual ~Ball();

	void update(float dt);

private:
	Vector2 _speed;
	void vBounce();
	void hBounce();
};

