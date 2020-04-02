#include "DrawableRect.h"

DrawableRect::DrawableRect(): Drawable(Vector2(0, 0)), color(Color())
{
	rect = Rect(0, 0, 1, 1);
}

DrawableRect::DrawableRect(const Vector2& position_, int w, int h, const Color& color_, SDL_Renderer& renderer): Drawable(position_), color(color_)
{
	rect = Rect(0, 0, w, h);
}


DrawableRect::~DrawableRect()
{
}

void DrawableRect::draw(SDL_Renderer& renderer)
{
	SDL_SetRenderDrawColor(&renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(&renderer, rect.to_sdl_rect(position));
	SDL_SetRenderDrawColor(&renderer, 0, 0, 0, 255);
}
