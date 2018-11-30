#pragma once
#include <SDL.h>
#include "Vector2.h"
#include "Color.h"
#include "Drawable.h"

class DrawableCircle : public Drawable
{
public:
	DrawableCircle();
	DrawableCircle(const Vector2& position, int radius, const Color& color, SDL_Renderer& renderer);
	virtual ~DrawableCircle();

	void draw(SDL_Renderer& renderer);

protected:
	int _radius;
	Color _color;

	SDL_Surface* _surface;
	SDL_Texture* _texture;
};

