#pragma once
#include <SDL.h>

struct Color
{
	Color() {
		r = 255;
		g = 255;
		b = 255;
		a = 255;
	}

	Color(int r_, int g_, int b_, int a_) {
		r = r_;
		g = g_;
		b = b_;
		a = a_;
	}

	SDL_Color to_sdl_color() {
		SDL_Color c;
		c.r = r;
		c.g = g;
		c.b = b;
		c.a = a;
		return c;
	}

	Uint32 to_Uint32() {
		return ((r & 0xff) << 24) + ((g & 0xff) << 16) + ((b & 0xff) << 8) + (a & 0xff);
	}

	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
};