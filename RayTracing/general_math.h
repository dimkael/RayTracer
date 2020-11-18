#pragma once

#include <cmath>
#include <limits>

const double inf = std::numeric_limits<double>::infinity();
const double pi = acos(-1.0);

inline static double degrees_to_radians(double degrees) {
	return degrees * pi / 180.0;
}

inline static double random_double() {
	return rand() / (RAND_MAX + 1.0);
}

inline static double random_double(double min, double max) {
	return min + (max - min) * random_double();
}

inline static double clamp(double x, double min, double max) {
	if (x < min) return min;
	if (x > max) return max;
	return x;
}