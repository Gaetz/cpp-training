#pragma once
#include <SDL.h>
#include "Vector2.h"
#include "Color.h"
#include "Drawable.h"

class DrawableCircle : public Drawable
{
public:
	DrawableCircle();
	DrawableCircle(const Vector2& position_, int radius_, const Color& color_, SDL_Renderer& renderer_);
	virtual ~DrawableCircle();

	void draw(SDL_Renderer& renderer_);
	int get_radius() const;

protected:
	int radius;
	Color color;
};

