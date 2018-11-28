#pragma once
class Vector2
{
public:
	Vector2();
	Vector2(int x, int y);
	~Vector2();

	Vector2& operator+=(const Vector2& b);
	friend Vector2 operator+(Vector2 a, const Vector2& b);

	const int x();
	int& rx();
	void setX(const int x);

	const int y();
	int& ry();
	void setY(const int y);

private:
	int _x;
	int _y;
};

