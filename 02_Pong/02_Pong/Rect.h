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

	int x() const;
	int& rx();
	void setX(const int x);

	int y() const;
	int& ry();
	void setY(const int y);

	int w() const;
	int& rw();
	void setW(const int w);

	int h() const;
	int& rh();
	void setH(const int h);

private:
	int _x;
	int _y;
	int _w;
	int _h;
};

