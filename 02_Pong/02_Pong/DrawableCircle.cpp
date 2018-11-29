#include "DrawableCircle.h"
#include <math.h>

DrawableCircle::DrawableCircle(): Drawable(), _radius(1), _sides(1), _color(Color()), _full(true)
{
}

DrawableCircle::DrawableCircle(const Vector2& position, int radius, unsigned int sides, const Color& color, bool full): Drawable(position), _radius(radius), _color(color), _sides(sides), _full(full)
{
}

DrawableCircle::~DrawableCircle()
{
}

void DrawableCircle::draw(SDL_Renderer & renderer)
{
	renderCircle(_position, _radius, _sides, renderer);
}

void DrawableCircle::renderCircle(const Vector2& center, int radius, unsigned int sides, SDL_Renderer& renderer)
{
	if (sides == 0)
	{
		sides = static_cast<unsigned int>(floor(M_PI * 2 * radius / 2));
	}

	float delta = static_cast<float>(M_PI * 2 / sides);
	float angle = delta;

	Vector2 start, end;
	if (_full) {
		bool startDraw = false;
		for (int i = -radius + center.y(); i <= radius + center.y(); ++i) {
			for (int j = -radius + center.x(); j <= radius + center.x(); ++j) {
				Vector2 v = Vector2(j, i);
				if (!startDraw && center.distance(v) <= radius) {
					startDraw = true;
					start = v;
				}
				if (startDraw && center.distance(v) >= radius) {
					startDraw = false;
					end = v;
				}
			}
			renderLine(start, end, renderer);
		}
	}
	else 
	{
		end.setX(radius);
		end.setY(0);
		end = end + center;
		for (int i = 0; i != sides; i++)
		{
			start = end;
			end.setX((int)roundf(static_cast<float>(cos(angle)) * radius));
			end.setY((int)roundf(static_cast<float>(sin(angle)) * radius));
			end = end + center;
			angle += delta;
			renderLine(start, end, renderer);
		}
	}


}

void DrawableCircle::renderLine(const Vector2& start, const Vector2& end, SDL_Renderer& renderer)
{
	SDL_SetRenderDrawColor(&renderer, _color.r, _color.g, _color.b, _color.a);
	SDL_RenderDrawLine(&renderer, start.x(), start.y(), end.x(), end.y());
	SDL_SetRenderDrawColor(&renderer, 0, 0, 0, 255);
}
