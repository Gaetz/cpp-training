#pragma once
class Vector2
{
public:
	Vector2();
	Vector2(float x, float y);
	~Vector2();

	float distance(Vector2& other) const;

	Vector2& operator+=(const Vector2& b);
	friend Vector2 operator+(Vector2 a, const Vector2& b);
	friend Vector2 operator*(Vector2 a, const float mult);

	float x() const;
	float& rx();
	void setX(const float x);

	float y() const;
	float& ry();
	void setY(const float y);

private:
	float _x;
	float _y;
};

