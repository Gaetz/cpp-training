#pragma once

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

	int r;
	int g;
	int b;
	int a;
};