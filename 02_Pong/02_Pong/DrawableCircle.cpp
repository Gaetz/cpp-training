#include "DrawableCircle.h"
#include <math.h>

DrawableCircle::DrawableCircle(): Drawable(), radius_(1), color_(Color())
{
}

DrawableCircle::DrawableCircle(const Vector2& position, int radius,  const Color& color, SDL_Renderer& renderer): Drawable(position), radius_(radius), color_(color)
{
}

DrawableCircle::~DrawableCircle()
{
}

void DrawableCircle::draw(SDL_Renderer & renderer)
{
	static const int BPP = 4;
	for (double dy = 1; dy <= radius_; dy += 1.0)
	{
		double dx = floor(sqrt((2.0 * radius_ * dy) - (dy * dy)));
		float cx = position_.x();
		double x = cx - dx;
		float cy = position_.y();
		SDL_SetRenderDrawColor(&renderer, color_.r, color_.g, color_.b, color_.a);
		SDL_RenderDrawLine(&renderer, static_cast<int>(cx - dx), static_cast<int>(cy + dy - radius_), static_cast<int>(cx + dx), static_cast<int>(cy + dy - radius_));
		SDL_RenderDrawLine(&renderer, static_cast<int>(cx - dx), static_cast<int>(cy - dy + radius_), static_cast<int>(cx + dx), static_cast<int>(cy - dy + radius_));
		SDL_SetRenderDrawColor(&renderer, 0, 0, 0, 255);
	}
}

int DrawableCircle::radius()
{
	return radius_;
}
