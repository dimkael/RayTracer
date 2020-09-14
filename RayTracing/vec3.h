#pragma once

#include <cmath>
#include <iostream>

class Vec3 {
public:
	Vec3();
	Vec3(double v1, double v2, double v3);

	double x() const;
	double y() const;
	double z() const;
	
	double operator[](int i) const;
	double& operator[](int i);

	Vec3 operator-() const;
	Vec3& operator+=(const Vec3& v);
	Vec3& operator*=(const double t);
	Vec3& operator/=(const double t);
	
	double length() const;
	double length_squared() const;

public:
	double vec3[3];
};

std::ostream& operator<<(std::ostream& out, const Vec3& v);

Vec3 operator+(const Vec3& u, const Vec3& v);
Vec3 operator-(const Vec3& u, const Vec3& v);
Vec3 operator*(const Vec3& u, const Vec3& v);
Vec3 operator*(double t, const Vec3& v);
Vec3 operator*(const Vec3& v, double t);
Vec3 operator/(const Vec3& v, double t);

double dot(const Vec3& u, const Vec3& v);
Vec3 cross(const Vec3& u, const Vec3& v);

Vec3 unit_vector(Vec3 v);

using Point3 = Vec3;
using Color = Vec3;