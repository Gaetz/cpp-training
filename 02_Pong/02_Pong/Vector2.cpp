#include "Vector2.h"
#include <math.h>

Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2(float x_, float y_)
{
	x = x_;
	y = y_;
}

Vector2::~Vector2()
{
}

float Vector2::distance(Vector2 & other) const
{
	return static_cast<float>(sqrt(pow(x - other.get_x(), 2) + pow(y - other.get_y(), 2)));
}

Vector2 & Vector2::operator+=(const Vector2 & b)
{
	x += b.x;
	y += b.y;
	return *this;
}

Vector2 operator+(Vector2 a, const Vector2 & b)
{
	a += b;
	return a;
}

Vector2 operator*(Vector2 a, const float mult)
{
	return Vector2(a.x * mult, a.y * mult);
}

float Vector2::get_x() const
{
	return x;
}

float & Vector2::r_x()
{
	return x;
}

void Vector2::set_x(const float x_)
{
	x = x_;
}

float Vector2::get_y() const
{ 
	return y;
}

float & Vector2::r_y()
{
	return y;
}

void Vector2::set_y(const float y_)
{
	y = y_;
}
