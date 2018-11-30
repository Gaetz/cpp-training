#pragma once
#include "Drawable.h"
#include "Rect.h"
#include "Color.h"

class DrawableRect : public Drawable
{
public:
	DrawableRect();
	DrawableRect(const Vector2& position, int w, int h, const Color& color, SDL_Renderer& renderer);
	virtual ~DrawableRect();

	void draw(SDL_Renderer& renderer);

private:
	Rect _rect;
	Color _color;
};

