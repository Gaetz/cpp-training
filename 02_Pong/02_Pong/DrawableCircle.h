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
	int radius();

protected:
	int radius_;
	Color color_;

	SDL_Surface* surface_;
	SDL_Texture* texture_;
};

