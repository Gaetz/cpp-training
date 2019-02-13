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

	int get_x() const;
	int& r_x();
	void set_x(const int x);

	int get_y() const;
	int& r_y();
	void set_y(const int y);

	int get_w() const;
	int& r_w();
	void set_w(const int w);

	int get_h() const;
	int& r_h();
	void set_h(const int h);

private:
	int x;
	int y;
	int w;
	int h;
};

