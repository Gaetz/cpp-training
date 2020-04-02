#pragma once
#include "Drawable.h"
#include "Rect.h"
#include "Color.h"

class DrawableRect : public Drawable
{
public:
	DrawableRect();
	DrawableRect(const Vector2& position_, int w, int h, const Color& color_, SDL_Renderer& renderer);
	virtual ~DrawableRect();

	void draw(SDL_Renderer& renderer);

private:
	Rect rect;
	Color color;
};

