#pragma once

#include <memory>
#include "vec3.h"
#include "ray.h"
#include "pixel.h"
#include "hittable_list.h"
#include "sphere.h"
#include "general_math.h"
#include "camera.h"

bool antialiasing = false;
const int MAX_DEPTH = 50;

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

Color ray_color(const Ray& ray, const Hittable& world, int depth) {
	if (depth <= 0) return Color(0.0, 0.0, 0.0);
	
	HitRecord hit_rec;
	if (world.hit(ray, 0.001, inf, hit_rec)) {
		//Point3 target = hit_rec.point + hit_rec.normal + unit_sphere_rand();
		//Point3 target = hit_rec.point + hit_rec.normal + random_unit_vector();
		Point3 target = hit_rec.point + hit_rec.normal + hemisphere_rand(hit_rec.normal);
		return 0.5 * ray_color(Ray(hit_rec.point, target - hit_rec.point), world, depth - 1);
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
			Pixel pixel(i, image_height - j);
			Ray ray;

			if (antialiasing) {
				for (int k = 0; k < 2; k++) {
					double u = (i + pow(-1.0, k) * 0.2) / (image_width - 1.0);
					for (int l = 0; l < 2; l++) {
						double v = (j + pow(-1.0, l) * 0.2) / (image_height - 1.0);
						ray = camera.get_ray(u, v);
						pixel.color += ray_color(ray, world, MAX_DEPTH);
					}
				}
				pixel.color /= 4.0;
			}
			else {
				double u = i / (image_width - 1.0);
				double v = j / (image_height - 1.0);
				ray = camera.get_ray(u, v);
				pixel.color += ray_color(ray, world, MAX_DEPTH);
			}

			pixel.draw(hdc);
		}
	}
}