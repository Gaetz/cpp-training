#pragma once
class Vector2
{
public:
	Vector2();
	Vector2(int x, int y);
	~Vector2();

	float distance(Vector2& other) const;

	Vector2& operator+=(const Vector2& b);
	friend Vector2 operator+(Vector2 a, const Vector2& b);

	int x() const;
	int& rx();
	void setX(const int x);

	int y() const;
	int& ry();
	void setY(const int y);

private:
	int _x;
	int _y;
};

