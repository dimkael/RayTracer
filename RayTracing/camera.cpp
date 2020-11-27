#include "camera.h"

Camera::Camera(Point3 lookfrom, Point3 lookat, Vec3 vup, double vfov, 
	int image_width, int image_height, double aperture, double focus_distance) {
	double aspect_ratio = double(image_width) / double(image_height);
	double theta = degrees_to_radians(vfov);
	double h = tan(theta / 2);

	viewport_height = 2.0 * h;
	viewport_width = viewport_height * aspect_ratio;

	w = unit_vector(lookfrom - lookat);
	u = unit_vector(cross(vup, w));
	v = cross(w, u);

	origin = lookfrom;
	horizontal = focus_distance * viewport_width * u;
	vertical = focus_distance * viewport_height * v;
	lower_left_corner = origin - horizontal / 2 - vertical / 2 - focus_distance * w;

	lens_radius = aperture / 2;
}

Ray Camera::get_ray(double s, double t) const {
	Vec3 rd = lens_radius * unit_disk_random();
	Vec3 offset = u * rd.x() + v * rd.y();

	return Ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset);
}