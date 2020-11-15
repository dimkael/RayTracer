#pragma once

#include "vec3.h"
#include "color.h"
#include "ray.h"

double viewport_width, viewport_height;
double focal_length = 1.0;

Point3 origin;
Vec3 horizontal, vertical;
Point3 lower_left_corner;

void perspective(double image_width, double image_height) {
	double aspect_ratio = image_width / image_height;
	viewport_width = 5.0;
	viewport_height = viewport_width / aspect_ratio;

	horizontal = Vec3(viewport_width, 0.0, 0.0);
	vertical = Vec3(0.0, viewport_height, 0.0);
	lower_left_corner = origin - horizontal / 2 - vertical / 2 - Vec3(0.0, 0.0, focal_length);
}

double hit_sphere(const Point3& center, double radius, const Ray& ray) {
	Vec3 oc = ray.origin() - center;
	double a = ray.direction().length_squared();
	double half_b = dot(oc, ray.direction());
	double c = oc.length_squared() - radius * radius;
	double d = half_b * half_b - a * c;

	if (d < 0) {
		return -1.0;
	}
	else {
		return (-half_b - sqrt(d) / a);
	}
}

Color ray_color(const Ray& ray) {
	double t = hit_sphere(Point3(0.0, 0.0, -1.0), 0.5, ray);
	if (t > 0.0) {
		Vec3 N = unit_vector(ray.at(t) - Vec3(0.0, 0.0, -1.0));
		return 0.5 * Color(N.x() + 1.0, N.y() + 1.0, N.z() + 1.0);
	}

	Vec3 unit_direction = unit_vector(ray.direction());
	t = 0.5 * (unit_direction.y() + 1.0);

	return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}


void draw(HDC& hdc, int image_width, int image_height) {
	perspective(image_width, image_height);

	for (int j = image_height - 1; j >= 0; j--) {
		for (int i = 0; i < image_width; i++) {
			double u = double(i) / (image_width - 1.0);
			double v = double(j) / (image_height - 1.0);

			Ray ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
			Color pixel_color = ray_color(ray);

			SetPixel(hdc, i, image_height - j, RGB(255.999 * pixel_color.x(), 255.999 * pixel_color.y(), 255.999 * pixel_color.z()));
		}
	}
}