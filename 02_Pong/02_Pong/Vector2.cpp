#include "Vector2.h"
#include <math.h>

Vector2::Vector2()
{
	_x = 0;
	_y = 0;
}

Vector2::Vector2(int x, int y)
{
	_x = x;
	_y = y;
}

Vector2::~Vector2()
{
}

float Vector2::distance(Vector2 & other) const
{
	return static_cast<float>(sqrt(pow(_x - other.x(), 2) + pow(_y - other.y(), 2)));
}

Vector2 & Vector2::operator+=(const Vector2 & b)
{
	_x += b._x;
	_y += b._y;
	return *this;
}

Vector2 operator+(Vector2 a, const Vector2 & b)
{
	a += b;
	return a;
}

int Vector2::x() const
{
	return _x;
}

int & Vector2::rx()
{
	return _x;
}

void Vector2::setX(const int x)
{
	_x = x;
}

int Vector2::y() const
{ 
	return _y;
}

int & Vector2::ry()
{
	return _y;
}

void Vector2::setY(const int y)
{
	_y = y;
}
