#include "vec3.h"


Vec3::Vec3() : vec3{ 0.0, 0.0, 0.0 } {}
Vec3::Vec3(double v1, double v2, double v3) : vec3{ v1, v2, v3 } {}


double Vec3::x() const { return vec3[0]; }
double Vec3::y() const { return vec3[1]; }
double Vec3::z() const { return vec3[2]; }


double Vec3::operator[](int i) const { return vec3[i]; }
double& Vec3::operator[](int i) { return vec3[i]; }



Vec3 Vec3::operator-() const { return Vec3(vec3[0], vec3[1], vec3[2]); }

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



inline Vec3 Vec3::random() {
	return Vec3(random_double(), random_double(), random_double());
}

inline Vec3 Vec3::random(double min, double max) {
	return Vec3(random_double(min, max), random_double(min, max), random_double(min, max));
}



bool Vec3::near_zero() const {
	const double s = 1e-8;
	return (fabs(vec3[0]) < s) && (fabs(vec3[1]) < s) && (fabs(vec3[2]) < s);
}



Vec3 operator+(const Vec3& u, const Vec3& v) {
	return Vec3(u.vec3[0] + v.vec3[0], u.vec3[1] + v.vec3[1], u.vec3[2] + v.vec3[2]);
}

Vec3 operator-(const Vec3& u, const Vec3& v) {
	return Vec3(u.vec3[0] - v.vec3[0], u.vec3[1] - v.vec3[1], u.vec3[2] - v.vec3[2]);
}

Vec3 operator*(const Vec3& u, const Vec3& v) {
	return Vec3(u.vec3[0] * v.vec3[0], u.vec3[1] * v.vec3[1], u.vec3[2] * v.vec3[2]);
}

Vec3 operator*(double t, const Vec3& v) {
	return Vec3(t * v.vec3[0], t * v.vec3[1], t * v.vec3[2]);
}

Vec3 operator*(const Vec3& v, double t) {
	return t * v;
}

Vec3 operator/(const Vec3& v, double t) {
	return (1/t) * v;
}



double dot(const Vec3& u, const Vec3& v) {
	return u.vec3[0] * v.vec3[0] + u.vec3[1] * v.vec3[1] + u.vec3[2] * v.vec3[2];
}

Vec3 cross(const Vec3& u, const Vec3& v) {
	return Vec3(u.vec3[1] * v.vec3[2] - u.vec3[2] * v.vec3[1],
				u.vec3[2] * v.vec3[0] - u.vec3[0] * v.vec3[2],
				u.vec3[0] * v.vec3[1] - u.vec3[1] * v.vec3[0]);
}



Vec3 unit_vector(Vec3 v) {
	return v / v.length();
}

Vec3 unit_sphere_rand() {
	while (true) {
		Vec3 p = Vec3::random(-1.0, 1.0);
		if (p.length_squared() >= 1.0) continue;

		return p;
	}
}

Vec3 random_unit_vector() {
	return unit_vector(unit_sphere_rand());
}

Vec3 hemisphere_rand(const Vec3& normal) {
	Vec3 unit_sphere_vector = unit_sphere_rand();
	if (dot(unit_sphere_vector, normal) > 0.0)
		return unit_sphere_vector;
	else
		return -unit_sphere_vector;
}



Vec3 reflect(const Vec3& v, const Vec3& n) {
	return v - 2 * dot(v, n) * n;
}

Vec3 refract(const Vec3& uv, const Vec3& n, double eta) {
	double cos_theta = fmin(dot(-uv, n), 1.0);
	Vec3 r_out_perp = eta * (uv + cos_theta * n);
	Vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;

	return r_out_perp + r_out_parallel;
}