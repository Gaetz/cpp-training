#include "Rect.h"

Rect::Rect()
{
	x = 0;
	y = 0;
	w = 1;
	h = 1;
}

Rect::Rect(int x_, int y_, int w_, int h_)
{
	x = x_;
	y = y_;
	w = w_;
	h = h_;
}

Rect::~Rect()
{
}

std::unique_ptr<SDL_Rect> Rect::to_sdl_rect(Vector2 position)
{
	std::unique_ptr<SDL_Rect> rect = std::make_unique<SDL_Rect>();
	rect->x = position._x() + x;
	rect->y = position._y() + y;
	rect->w = w;
	rect->h = h;
	return rect;
}

int Rect::_x() const
{
	return x;
}

int & Rect::r_x()
{
	return x;
}

void Rect::s_x(const int x_)
{
	x = x_;
}

int Rect::_y() const
{
	return y;
}

int & Rect::r_y()
{
	return y;
}

void Rect::s_y(const int y_)
{
	y = y_;
}

int Rect::_w() const
{
	return w;
}

int & Rect::r_w()
{
	return w;
}

void Rect::s_w(const int w_)
{
	w = w_;
}

int Rect::_h() const
{
	return h;
}

int & Rect::r_h()
{
	return h;
}

void Rect::s_h(const int h_)
{
	h = h_;
}
