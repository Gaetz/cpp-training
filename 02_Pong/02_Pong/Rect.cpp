#include "Rect.h"

Rect::Rect()
{
	x_ = 0;
	y_ = 0;
	w_ = 1;
	h_ = 1;
}

Rect::Rect(int x, int y, int w, int h)
{
	x_ = x;
	y_ = y;
	w_ = w;
	h_ = h;
}

Rect::~Rect()
{
}

std::unique_ptr<SDL_Rect> Rect::toSDLRect(Vector2 position)
{
	std::unique_ptr<SDL_Rect> rect = std::make_unique<SDL_Rect>();
	rect->x = position.x() + x_;
	rect->y = position.y() + y_;
	rect->w = w_;
	rect->h = h_;
	return rect;
}

int Rect::x() const
{
	return x_;
}

int & Rect::rx()
{
	return x_;
}

void Rect::setX(const int x)
{
	x_ = x;
}

int Rect::y() const
{
	return y_;
}

int & Rect::ry()
{
	return y_;
}

void Rect::setY(const int y)
{
	y_ = y;
}

int Rect::w() const
{
	return w_;
}

int & Rect::rw()
{
	return w_;
}

void Rect::setW(const int w)
{
	w_ = w;
}

int Rect::h() const
{
	return h_;
}

int & Rect::rh()
{
	return h_;
}

void Rect::setH(const int h)
{
	h_ = h;
}
