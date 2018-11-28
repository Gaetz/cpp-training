#include "DrawableRect.h"

DrawableRect::DrawableRect()
{
	_position = Vector2();
	_color.r = 255;
	_color.g = 255;
	_color.b = 255;
	_color.a = 255;
}

DrawableRect::DrawableRect(const Vector2& position, int w, int h, Color color)
{
	_position = position;
	_rect = Rect(0, 0, w, h);
	_color = color;
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