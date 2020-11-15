#pragma once

#include <Windows.h>
#include "vec3.h"

class Pixel {
public:
	Pixel();
	Pixel(int _x, int _y, int _samples);

	void draw(HDC hdc);
	
public:
	int x, y;
	int samples;
	Color color;
};