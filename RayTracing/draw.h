#pragma once

#include <memory>
#include "vec3.h"
#include "ray.h"
#include "pixel.h"
#include "hittable_list.h"
#include "sphere.h"
#include "general_math.h"
#include "camera.h"

const int antialiasing_multiplier = 8;

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

Color ray_color(const Ray& ray, const Hittable& world) {
	HitRecord hit_rec;
	if (world.hit(ray, 0.0, inf, hit_rec)) {
		return 0.5 * (hit_rec.normal + Color(1.0, 1.0, 1.0));
	}

	Vec3 unit_direction = unit_vector(ray.direction());
	double t = 0.5 * (unit_direction.y() + 1.0);

	return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}


void draw(HDC& hdc, int image_width, int image_height) {
	HittableList world;
	world.add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5));
	world.add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100));

	Camera camera(image_width, image_height);

	for (int j = image_height - 1; j >= 0; j--) {
		for (int i = 0; i < image_width; i++) {
			Pixel pixel(i, image_height - j, antialiasing_multiplier);
			for (int s = 0; s < antialiasing_multiplier; s++) {
				double u = (i + random_double()) / (image_width - 1.0);
				double v = (j + random_double()) / (image_height - 1.0);

				Ray ray = camera.get_ray(u, v);
				pixel.color += ray_color(ray, world);
			}
			pixel.draw(hdc);
		}
	}
}