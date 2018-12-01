#include "Vector2.h"
#include <math.h>

Vector2::Vector2()
{
	x_ = 0;
	y_ = 0;
}

Vector2::Vector2(float x, float y)
{
	x_ = x;
	y_ = y;
}

Vector2::~Vector2()
{
}

float Vector2::distance(Vector2 & other) const
{
	return static_cast<float>(sqrt(pow(x_ - other.x(), 2) + pow(y_ - other.y(), 2)));
}

Vector2 & Vector2::operator+=(const Vector2 & b)
{
	x_ += b.x_;
	y_ += b.y_;
	return *this;
}

Vector2 operator+(Vector2 a, const Vector2 & b)
{
	a += b;
	return a;
}

Vector2 operator*(Vector2 a, const float mult)
{
	return Vector2(a.x_ * mult, a.y_ * mult);
}

float Vector2::x() const
{
	return x_;
}

float & Vector2::rx()
{
	return x_;
}

void Vector2::setX(const float x)
{
	x_ = x;
}

float Vector2::y() const
{ 
	return y_;
}

float & Vector2::ry()
{
	return y_;
}

void Vector2::setY(const float y)
{
	y_ = y;
}
