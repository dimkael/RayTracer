#include <iostream>
#include "vec3.h"
#include "color.h"
#include "ray.h"

// 1,125

bool hit_sphere(const Point3& center, double radius, const Ray& ray) {
	Vec3 oc = ray.origin() - center;
	double a = dot(ray.direction(), ray.direction());
	double b = 2.0 * dot(oc, ray.direction());
	double c = dot(oc, oc) - radius * radius;
	double d = b * b - 4 * a * c;
	return d > 0;
}

Color ray_color(const Ray& ray) {
	if (hit_sphere(Point3(0.0, 0.0, -1.0), 0.5, ray))
		return Color(1.0, 0.0, 0.0);

	Vec3 unit_direction = unit_vector(ray.direction());
	double t = 0.5 * (unit_direction.y() + 1.0);

	return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

int main() {
	const double aspect_ratio = 16.0 / 9.0;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio);

	double viewport_height = 2.0;
	double viewport_width = aspect_ratio * viewport_height;
	double focal_length = 1.0;

	Point3 origin = Point3(0.0, 0.0, 0.0);
	Vec3 horizontal = Vec3(viewport_width, 0.0, 0.0);
	Vec3 vertical = Vec3(0.0, viewport_height, 0.0);
	Point3 lower_left_corner = origin - horizontal / 2 - vertical / 2 - Vec3(0.0, 0.0, focal_length);

	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; j--) {
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < image_width; i++) {
			double u = double(i) / (image_width - 1);
			double v = double(j) / (image_height - 1);
			
			Ray ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
			Color pixel_color = ray_color(ray);

			write_color(std::cout, pixel_color);
		}
	}

	std::cerr << "\nDone.\n";

	return 0;
}