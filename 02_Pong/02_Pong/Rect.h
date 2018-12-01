#pragma once
#include <SDL.h>
#include <memory>
#include "Vector2.h"

class Rect
{
public:
	Rect();
	Rect(int x, int y, int w, int h);
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
	int x_;
	int y_;
	int w_;
	int h_;
};

