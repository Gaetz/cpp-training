#include "Rect.h"

Rect::Rect()
{
	x = 0;
	y = 0;
	w = 1;
	h = 1;
	rect = SDL_Rect();
}

Rect::Rect(int x_, int y_, int w_, int h_)
{
	x = x_;
	y = y_;
	w = w_;
	h = h_;
	rect = SDL_Rect();
}

Rect::~Rect()
{
}

const SDL_Rect* Rect::to_sdl_rect(Vector2 position)
{
	rect.x = position.get_x() + x;
	rect.y = position.get_y() + y;
	rect.w = w;
	rect.h = h;
	return &rect;
}

int Rect::get_x() const
{
	return x;
}

int & Rect::r_x()
{
	return x;
}

void Rect::set_x(const int x_)
{
	x = x_;
}

int Rect::get_y() const
{
	return y;
}

int & Rect::r_y()
{
	return y;
}

void Rect::set_y(const int y_)
{
	y = y_;
}

int Rect::get_w() const
{
	return w;
}

int & Rect::r_w()
{
	return w;
}

void Rect::set_w(const int w_)
{
	w = w_;
}

int Rect::get_h() const
{
	return h;
}

int & Rect::r_h()
{
	return h;
}

void Rect::set_h(const int h_)
{
	h = h_;
}
