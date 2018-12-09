#pragma once
#include "Vector2.h"
#include <SDL.h>

class Input
{
public:
	Input();
	~Input();

	static bool update();

	static Vector2 mousePos();
	static bool leftButtonClicked();
	static bool leftButtonJustClicked();
	static bool leftButtonJustReleased();

private:
	static int mouse_x_;
	static int mouse_y_;
	static bool leftButtonClicked_;
	static bool leftButtonJustClicked_;
	static bool leftButtonJustReleased_;
};

