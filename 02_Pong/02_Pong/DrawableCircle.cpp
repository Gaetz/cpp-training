#include "DrawableCircle.h"
#include <math.h>

DrawableCircle::DrawableCircle(): Drawable(), radius(1), color(Color())
{
}

DrawableCircle::DrawableCircle(const Vector2& position_, int radius_,  const Color& color_, SDL_Renderer& renderer_):
	Drawable(position_), radius(radius_), color(color_)
{
}

DrawableCircle::~DrawableCircle()
{
}

void DrawableCircle::draw(SDL_Renderer & renderer)
{
	for (double dy = 1; dy <= radius; dy += 1.0)
	{
		double dx = floor(sqrt((2.0 * radius * dy) - (dy * dy)));
		float cx = position._x();
		double x = cx - dx;
		float cy = position._y();
		SDL_SetRenderDrawColor(&renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawLine(&renderer, static_cast<int>(cx - dx), static_cast<int>(cy + dy - radius), static_cast<int>(cx + dx), static_cast<int>(cy + dy - radius));
		SDL_RenderDrawLine(&renderer, static_cast<int>(cx - dx), static_cast<int>(cy - dy + radius), static_cast<int>(cx + dx), static_cast<int>(cy - dy + radius));
		SDL_SetRenderDrawColor(&renderer, 0, 0, 0, 255);
	}
}

int DrawableCircle::_radius() const
{
	return radius;
}
