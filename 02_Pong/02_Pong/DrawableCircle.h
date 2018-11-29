#pragma once
#include <SDL.h>
#include "Vector2.h"
#include "Color.h"
#include "Drawable.h"

class DrawableCircle : public Drawable
{
public:
	DrawableCircle();
	DrawableCircle(const Vector2& position, int radius, unsigned int sides, const Color& color, bool full);
	virtual ~DrawableCircle();

	void draw(SDL_Renderer& renderer);

protected:
	int _radius;
	Color _color;
	unsigned int _sides;
	bool _full;

	SDL_Surface* surface;
	SDL_Texture* texture;

	void renderCircle(const Vector2& center, int radius, unsigned int sides, SDL_Renderer& renderer);
	void renderLine(const Vector2& start, const Vector2& end, SDL_Renderer& renderer);

};

