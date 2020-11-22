#pragma once

#include "general_math.h"

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

	inline static Vec3 random();
	inline static Vec3 random(double min, double max);

	bool near_zero() const;

public:
	double vec3[3];
};

Vec3 operator+(const Vec3& u, const Vec3& v);
Vec3 operator-(const Vec3& u, const Vec3& v);
Vec3 operator*(const Vec3& u, const Vec3& v);
Vec3 operator*(double t, const Vec3& v);
Vec3 operator*(const Vec3& v, double t);
Vec3 operator/(const Vec3& v, double t);

double dot(const Vec3& u, const Vec3& v);
Vec3 cross(const Vec3& u, const Vec3& v);

Vec3 unit_vector(Vec3 v);
Vec3 unit_sphere_rand();
Vec3 random_unit_vector();
Vec3 hemisphere_rand(const Vec3& normal);

Vec3 reflect(const Vec3& v, const Vec3& n);

using Point3 = Vec3;
using Color = Vec3;