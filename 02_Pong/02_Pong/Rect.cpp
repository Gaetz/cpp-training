#include "Rect.h"

Rect::Rect()
{
	_x = 0;
	_y = 0;
	_w = 1;
	_h = 1;
}

Rect::Rect(int x, int y, int w, int h)
{
	_x = x;
	_y = y;
	_w = w;
	_h = h;
}

Rect::~Rect()
{
}

std::unique_ptr<SDL_Rect> Rect::toSDLRect(Vector2 position)
{
	std::unique_ptr<SDL_Rect> rect = std::make_unique<SDL_Rect>();
	rect->x = position.x() + _x;
	rect->y = position.y() + _y;
	rect->w = _w;
	rect->h = _h;
	return rect;
}

int Rect::x() const
{
	return _x;
}

int & Rect::rx()
{
	return _x;
}

void Rect::setX(const int x)
{
	_x = x;
}

int Rect::y() const
{
	return _y;
}

int & Rect::ry()
{
	return _y;
}

void Rect::setY(const int y)
{
	_y = y;
}

int Rect::w() const
{
	return _w;
}

int & Rect::rw()
{
	return _w;
}

void Rect::setW(const int w)
{
	_w = w;
}

int Rect::h() const
{
	return _h;
}

int & Rect::rh()
{
	return _h;
}

void Rect::setH(const int h)
{
	_h = h;
}
