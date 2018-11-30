#pragma once
#include "DrawableCircle.h"
#include "GameObject.h"

#include <SDL.h>

class Ball: public GameObject
{
public:
	Ball();
	Ball(Vector2& position, Vector2& speed, SDL_Renderer& renderer);
	virtual ~Ball();

	void update(float dt);
	void draw(SDL_Renderer& renderer);

private:
	DrawableCircle _graphics;
	Vector2 _speed;
	void vBounce();
	void hBounce();
};

