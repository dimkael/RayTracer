#include "vec3.h"


Vec3::Vec3() : vec3{ 0, 0, 0 } {}
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



std::ostream& operator<<(std::ostream& out, const Vec3& v) {
	return out << v.vec3[0] << ' ' << v.vec3[1] << ' ' << v.vec3[2];
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