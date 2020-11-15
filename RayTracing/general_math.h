#pragma once

#include <cmath>
#include <limits>

const double inf = std::numeric_limits<double>::infinity();
const double pi = acos(-1.0);

inline double degrees_to_radians(double degrees) {
	return degrees * pi / 180.0;
}