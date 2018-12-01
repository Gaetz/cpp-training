#include "DrawableRect.h"

DrawableRect::DrawableRect(): Drawable(Vector2(0, 0)), color_(Color(255, 255, 255, 255))
{
	rect_ = Rect(0, 0, 1, 1);
}

DrawableRect::DrawableRect(const Vector2& position, int w, int h, const Color& color, SDL_Renderer& renderer): Drawable(position), color_(color)
{
	rect_ = Rect(0, 0, w, h);
}


DrawableRect::~DrawableRect()
{
}

void DrawableRect::draw(SDL_Renderer& renderer) 
{
	SDL_SetRenderDrawColor(&renderer, color_.r, color_.g, color_.b, color_.a);
	SDL_RenderFillRect(&renderer, rect_.toSDLRect(position_).get());
	SDL_SetRenderDrawColor(&renderer, 0, 0, 0, 255);
}
