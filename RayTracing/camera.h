#pragma once

#include "vec3.h"
#include "ray.h"
#include "general_math.h"

class Camera {
public:
	Camera(int image_width, int image_height);

	Ray get_ray(double u, double v) const;

private:
	double viewport_width, viewport_height;
	double focal_length = 1.0;

	Point3 origin;
	Vec3 horizontal, vertical;
	Point3 lower_left_corner;
};