#pragma once
#include <SDL.h>
#include "Vector2.h"
class Drawable
{
public:
	virtual ~Drawable();

	virtual void draw(SDL_Renderer& renderer) = 0;

protected:
	Vector2 _position;
};

