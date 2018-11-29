#pragma once
#include "DrawableCircle.h"
class Ball :
	public DrawableCircle
{
public:
	Ball();
	Ball(Vector2& position, Vector2& speed);
	virtual ~Ball();

	void update(float dt);

private:
	Vector2 _speed;
	void vBounce();
	void hBounce();
};

