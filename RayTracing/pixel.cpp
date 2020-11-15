#include "pixel.h"

Pixel::Pixel() : x(0), y(0), samples(1) {}
Pixel::Pixel(int _x, int _y, int _samples) : x(_x), y(_y), samples(_samples) {}

void Pixel::draw(HDC hdc) {
	double scale = 1.0 / samples;
	color *= scale;

	SetPixel(hdc, x, y, RGB(255.999 * color.x(), 255.999 * color.y(), 255.999 * color.z()));
}