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

	Color(int rp, int gp, int bp, int ap) {
		r = rp;
		g = gp;
		b = bp;
		a = ap;
	}

	SDL_Color toSDLColor() {
		SDL_Color c;
		c.r = r;
		c.g = g;
		c.b = b;
		c.a = a;
		return c;
	}

	Uint32 toUint32() {
		return ((r & 0xff) << 24) + ((g & 0xff) << 16) + ((b & 0xff) << 8) + (a & 0xff);
	}

	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
};