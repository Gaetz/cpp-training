#pragma once
#include <SDL.h>
#include "Vector2.h"
class Drawable
{
public:
	Drawable();
	Drawable(const Vector2& position);
	virtual ~Drawable();

	void setPosition(Vector2 position);
	virtual void draw(SDL_Renderer& renderer) = 0;

protected:
	Vector2 position_;
};

