#include "Input.h"

Input::Input()
{
}


Input::~Input()
{
}

bool Input::leftButtonClicked_ = false;
bool Input::leftButtonJustClicked_ = false;
bool Input::leftButtonJustReleased_ = false;
int Input::mouse_x_ = 0;
int Input::mouse_y_ = 0;

Vector2 Input::mousePos()
{
	SDL_GetMouseState(&mouse_x_, &mouse_y_);
	return Vector2(static_cast<float>(mouse_x_), static_cast<float>(mouse_y_));
}

bool Input::leftButtonClicked()
{
	return leftButtonClicked_;
}

bool Input::leftButtonJustClicked()
{
	return leftButtonJustClicked_;
}

bool Input::leftButtonJustReleased()
{
	return leftButtonJustReleased_;
}

bool Input::update()
{
	SDL_Event event;
	// Manage variables
	if (leftButtonJustReleased_) {
		leftButtonJustReleased_ = false;
	}
	// Update events
	while (SDL_PollEvent(&event) != 0) {
		switch (event.type) {
		case SDL_QUIT:
			return true;
		case SDL_MOUSEBUTTONDOWN:
			if (leftButtonClicked_) {
				leftButtonJustClicked_ = false;
			}
			else {
				leftButtonClicked_ = true;
				leftButtonJustClicked_ = true;
			}
		case SDL_MOUSEBUTTONUP:
			if (leftButtonClicked_) {
				leftButtonClicked_ = false;
				leftButtonJustReleased_ = true;
			}
			return false;
		}
	}
}