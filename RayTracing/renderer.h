#pragma once

#include <memory>
#include "vec3.h"
#include "general_math.h"
#include "ray.h"
#include "pixel.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

bool antialiasing = true;
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
	
	HitRecord rec;
	if (world.hit(ray, 0.001, inf, rec)) {
		Ray scattered;
		Color attenuation;

		if (rec.material_ptr->scatter(ray, rec, attenuation, scattered))
			return attenuation * ray_color(scattered, world, depth - 1);

		return Color(0.0, 0.0, 0.0);
	}

	Vec3 unit_direction = unit_vector(ray.direction());
	double t = 0.5 * (unit_direction.y() + 1.0);

	return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

HittableList random_scene() {
	HittableList world;

	std::shared_ptr<Lambertian> ground_material = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
	world.add(std::make_shared<Sphere>(Point3(0.0, -1000.0, 0.0), 1000.0, ground_material));

	for (int i = -11; i < 11; i++) {
		for (int j = -11; j < 11; j++) {
			double chosen = random_double();
			Point3 center(i + 0.9 * random_double(), 0.2, j + 0.9 * random_double());

			if ((center - Point3(4.0, 0.2, 0.0)).length() > 0.9) {
				std::shared_ptr<Material> sphere_material;

				if (chosen < 0.8) {
					// Diffuse sphere
					Color albedo = Color::random() * Color::random();
					sphere_material = std::make_shared<Lambertian>(albedo);
					world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
				}
				else if (chosen < 0.95) {
					// Metal sphere
					Color albedo = Color::random(0.5, 1.0);
					double fuzziness = random_double(0.0, 0.5);
					sphere_material = std::make_shared<Metal>(albedo, fuzziness);
					world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
				}
				else {
					// Glass sphere
					sphere_material = std::make_shared<Dielectric>(1.5);
					world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
				}
			}
		}
	}

	std::shared_ptr<Dielectric> material1 = std::make_shared<Dielectric>(1.5);
	world.add(std::make_shared<Sphere>(Point3(0.0, 1.0, 0.0), 1.0, material1));
	std::shared_ptr<Lambertian> material2 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
	world.add(std::make_shared<Sphere>(Point3(-4.0, 1.0, 0.0), 1.0, material2));
	std::shared_ptr<Metal> material3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
	world.add(std::make_shared<Sphere>(Point3(4.0, 1.0, 0.0), 1.0, material3));

	return world;
}

void render(HDC& hdc, int image_width, int image_height) {
	HittableList world = random_scene();

	Point3 lookfrom(13.0, 2.0, 3.0);
	Point3 lookat(0.0, 0.0, 0.0);
	Vec3  vup(0.0, 1.0, 0.0);
	double distance_to_focus = 10.0;
	double aperture = 0.1;
	Camera camera(lookfrom, lookat, vup, 20, image_width, image_height, aperture, distance_to_focus);

	for (int j = image_height - 1; j >= 0; j--) {
		for (int i = 0; i < image_width; i++) {
			Pixel pixel(i, image_height - j);
			Ray ray;

			if (antialiasing) {
				/*for (int k = 0; k < 2; k++) {
					double u = (i + pow(-1.0, k) * 0.2) / (image_width - 1.0);
					for (int l = 0; l < 2; l++) {
						double v = (j + pow(-1.0, l) * 0.2) / (image_height - 1.0);
						ray = camera.get_ray(u, v);
						pixel.color += ray_color(ray, world, MAX_DEPTH);
					}
				}
				pixel.color /= 4.0;*/

				int antialiasing_multiplier = 20;
				for (int s = 0; s < antialiasing_multiplier; s++) {
					double u = (i + random_double()) / (image_width - 1);
					double v = (j + random_double()) / (image_height - 1);
					Ray ray = camera.get_ray(u, v);
					pixel.color += ray_color(ray, world, MAX_DEPTH);
				}
				pixel.color /= double(antialiasing_multiplier);
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