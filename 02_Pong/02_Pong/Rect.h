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

	std::unique_ptr<SDL_Rect> to_sdl_rect(Vector2 position);

	int _x() const;
	int& r_x();
	void s_x(const int x);

	int _y() const;
	int& r_y();
	void s_y(const int y);

	int _w() const;
	int& r_w();
	void s_w(const int w);

	int _h() const;
	int& r_h();
	void s_h(const int h);

private:
	int x;
	int y;
	int w;
	int h;
};

