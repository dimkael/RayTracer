#pragma once

#include "vec3.h"
#include "ray.h"
#include "general_math.h"

class Camera {
public:
	Camera(Point3 lookfrom, Point3 lookat, Vec3 vup, double vfov,
		int image_width, int image_height, double aperture, double focus_distance);

	Ray get_ray(double s, double t) const;

private:
	double viewport_width, viewport_height;
	double focal_length = 1.0;

	Point3 origin;
	Vec3 horizontal, vertical;
	Point3 lower_left_corner;

	Vec3 u, v, w;
	double lens_radius;
};