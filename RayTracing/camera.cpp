#include "camera.h"

Camera::Camera(int image_width, int image_height) {
	double aspect_ratio = double(image_width) / double(image_height);
	viewport_width = 5.0;
	viewport_height = viewport_width / aspect_ratio;

	origin = Point3(0, 0, 0);
	horizontal = Vec3(viewport_width, 0.0, 0.0);
	vertical = Vec3(0.0, viewport_height, 0.0);
	lower_left_corner = origin - horizontal / 2 - vertical / 2 - Vec3(0.0, 0.0, focal_length);
}

Ray Camera::get_ray(double u, double v) const {
	return Ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
}