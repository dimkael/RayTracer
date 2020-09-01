#pragma once

#include <cmath>
#include <iostream>

class Vec3 {
public:
	Vec3();
	Vec3(double v1, double v2, double v3);

	inline double x() const;
	inline double y() const;
	inline double z() const;

	Vec3 operator-() const;
	inline double operator[](int i) const;
	inline double& operator[](int i);

	Vec3& operator+=(const Vec3& v);
	Vec3& operator*=(const double t);
	Vec3& operator/=(const double t);
	
	double length() const;
	double length_squared() const;

public:
	double vec3[3];
};

using Point3 = Vec3;
using Color = Vec3;