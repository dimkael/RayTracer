#pragma once

#include <cmath>
#include <limits>

const double inf = std::numeric_limits<double>::infinity();
const double pi = acos(-1.0);

inline double degrees_to_radians(double degrees) {
	return degrees * pi / 180.0;
}

inline double random_double() {
	return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
	return min + (max - min) * random_double();
}

inline double clamp(double x, double min, double max) {
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

inline Point3 clamp(Point3 point, double min, double max) {
	return Point3(
		clamp(point.x(), min, max),
		clamp(point.y(), min, max),
		clamp(point.z(), min, max)
	);
}