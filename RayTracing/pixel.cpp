#include "pixel.h"

Pixel::Pixel() : x(0), y(0) {}
Pixel::Pixel(int _x, int _y) : x(_x), y(_y) {}

void Pixel::draw(HDC hdc) {
	color = clamp(color, 0.0, 0.999);
	SetPixel(hdc, x, y, RGB(256 * color.x(), 256 * color.y(), 256 * color.z()));
}