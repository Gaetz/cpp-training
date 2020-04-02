#pragma once
#include "Vector2.h"
#include <SDL.h>

class Input
{
public:
	Input();
	~Input();

	static bool update();

	static Vector2 mouse_pos();
	static bool left_button_clicked();
	static bool left_button_just_clicked();
	static bool left_button_just_released();

private:
	static int mouse_x;
	static int mouse_y;
	static bool is_left_button_clicked;
	static bool is_left_button_just_clicked;
	static bool is_left_button_just_released;
};

