#pragma once
#include <SDL.h>
#include <memory>
#include "Vector2.h"

class Rect
{
public:
	Rect();
	Rect(int _x, int _y, int _w, int _h);
	~Rect();

	std::unique_ptr<SDL_Rect> toSDLRect(Vector2 position);

	const int x();
	int& rx();
	void setX(const int x);

	const int y();
	int& ry();
	void setY(const int y);

	const int w();
	int& rw();
	void setW(const int w);

	const int h();
	int& rh();
	void setH(const int h);

private:
	int _x;
	int _y;
	int _w;
	int _h;
};

