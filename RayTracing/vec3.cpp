#include "vec3.h"

Vec3::Vec3() : vec3{ 0, 0, 0 } {}
Vec3::Vec3(double v1, double v2, double v3) : vec3{ v1, v2, v3 } {}

inline double Vec3::x() const { return vec3[0]; }
inline double Vec3::y() const { return vec3[1]; }
inline double Vec3::z() const { return vec3[2]; }

Vec3 Vec3::operator-() const { return Vec3(vec3[0], vec3[1], vec3[2]); }
inline double Vec3::operator[](int i) const { return vec3[i]; }
inline double& Vec3::operator[](int i) { return vec3[i]; }

Vec3& Vec3::operator+=(const Vec3& v) {
	vec3[0] += v.vec3[0];
	vec3[1] += v.vec3[1];
	vec3[2] += v.vec3[2];

	return *this;
}

Vec3& Vec3::operator*=(const double t) {
	vec3[0] *= t;
	vec3[1] *= t;
	vec3[2] *= t;

	return *this;
}

Vec3& Vec3::operator/=(const double t) {
	return *this *= 1 / t;
}

double Vec3::length() const {
	return sqrt(length_squared());
}

double Vec3::length_squared() const {
	return vec3[0] * vec3[0] + vec3[1] * vec3[1] + vec3[2] * vec3[2];
}