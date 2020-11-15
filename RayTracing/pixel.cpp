#include "pixel.h"

Pixel::Pixel() : x(0), y(0), samples(1) {}
Pixel::Pixel(int _x, int _y, int _samples) : x(_x), y(_y), samples(_samples) {}

void Pixel::draw(HDC hdc) {
	double scale = 1.0 / samples;
	color *= scale;
	color = clamp(color, 0.0, 0.999);

	SetPixel(hdc, x, y, RGB(256 * color.x(), 256 * color.y(), 256 * color.z()));
}