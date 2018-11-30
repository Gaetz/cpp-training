#include "DrawableCircle.h"
#include <math.h>

DrawableCircle::DrawableCircle(): Drawable(), _radius(1), _color(Color())
{
}

DrawableCircle::DrawableCircle(const Vector2& position, int radius,  const Color& color, SDL_Renderer& renderer): Drawable(position), _radius(radius), _color(color)
{
}

DrawableCircle::~DrawableCircle()
{
}

void DrawableCircle::draw(SDL_Renderer & renderer)
{
	static const int BPP = 4;
	for (double dy = 1; dy <= _radius; dy += 1.0)
	{
		double dx = floor(sqrt((2.0 * _radius * dy) - (dy * dy)));
		float cx = _position.x();
		double x = cx - dx;
		float cy = _position.y();
		SDL_SetRenderDrawColor(&renderer, _color.r, _color.g, _color.b, _color.a);
		SDL_RenderDrawLine(&renderer, static_cast<int>(cx - dx), cy + dy - _radius, cx + dx, cy + dy - _radius);
		SDL_RenderDrawLine(&renderer, cx - dx, cy - dy + _radius, cx + dx, cy - dy + _radius);
		SDL_SetRenderDrawColor(&renderer, 0, 0, 0, 255);
	}
}
