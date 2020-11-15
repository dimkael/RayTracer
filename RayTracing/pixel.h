#pragma once

#include <Windows.h>
#include "vec3.h"
#include "general_math.h"

class Pixel {
public:
	Pixel();
	Pixel(int _x, int _y);

	void draw(HDC hdc);
	
public:
	int x, y;
	Color color;
};