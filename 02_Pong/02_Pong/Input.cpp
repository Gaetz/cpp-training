#include "Input.h"

Input::Input()
{
}


Input::~Input()
{
}

bool Input::is_left_button_clicked = false;
bool Input::is_left_button_just_clicked = false;
bool Input::is_left_button_just_released = false;
int Input::mouse_x = 0;
int Input::mouse_y = 0;

Vector2 Input::mouse_pos()
{
	SDL_GetMouseState(&mouse_x, &mouse_y);
	return Vector2(static_cast<float>(mouse_x), static_cast<float>(mouse_y));
}

bool Input::left_button_clicked()
{
	return is_left_button_clicked;
}

bool Input::left_button_just_clicked()
{
	return is_left_button_just_clicked;
}

bool Input::left_button_just_released()
{
	return is_left_button_just_released;
}

bool Input::update()
{
	SDL_Event event;
	// Manage variables
	if (is_left_button_just_released) {
		is_left_button_just_released = false;
	}
	// Update events
	while (SDL_PollEvent(&event) != 0) {
		switch (event.type) {
		case SDL_QUIT:
			return true;
		case SDL_MOUSEBUTTONDOWN:
			if (is_left_button_clicked) {
				is_left_button_just_clicked = false;
			}
			else {
				is_left_button_clicked = true;
				is_left_button_just_clicked = true;
			}
		case SDL_MOUSEBUTTONUP:
			if (is_left_button_clicked) {
				is_left_button_clicked = false;
				is_left_button_just_released = true;
			}
			return false;
		}
	}
}