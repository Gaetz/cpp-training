#include "DrawableRect.h"

DrawableRect::DrawableRect(): Drawable(Vector2(0, 0)), _color(Color(255, 255, 255, 255))
{
	_rect = Rect(0, 0, 1, 1);
}

DrawableRect::DrawableRect(const Vector2& position, int w, int h, const Color& color): Drawable(position), _color(color)
{
	_rect = Rect(0, 0, w, h);
}


DrawableRect::~DrawableRect()
{
}

void DrawableRect::draw(SDL_Renderer& renderer) 
{
	SDL_SetRenderDrawColor(&renderer, _color.r, _color.g, _color.b, _color.a);
	SDL_RenderFillRect(&renderer, _rect.toSDLRect(_position).get());
	SDL_SetRenderDrawColor(&renderer, 0, 0, 0, 255);
}