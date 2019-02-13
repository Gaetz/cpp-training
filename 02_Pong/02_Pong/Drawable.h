#pragma once
#include <SDL.h>
#include "Vector2.h"
class Drawable
{
public:
	Drawable();
	Drawable(const Vector2& position_);
	virtual ~Drawable();

	void set_position(const Vector2& position_);
	virtual void draw(SDL_Renderer& renderer_) = 0;

protected:
	Vector2 position;
};

