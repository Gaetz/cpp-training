#pragma once
class Vector2
{
public:
	Vector2();
	Vector2(float x_, float y_);
	~Vector2();

	float distance(Vector2& other) const;

	Vector2& operator+=(const Vector2& b);
	friend Vector2 operator+(Vector2 a, const Vector2& b);
	friend Vector2 operator*(Vector2 a, const float mult);

	float get_x() const;
	float& r_x();
	void set_x(const float x);

	float get_y() const;
	float& r_y();
	void set_y(const float y);

private:
	float x;
	float y;
};

