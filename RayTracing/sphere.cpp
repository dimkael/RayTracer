#include "sphere.h"

Sphere::Sphere() : center(0.0, 0.0, 0.0), radius(0.0) {}

Sphere::Sphere(Point3 _center, double _radius, std::shared_ptr<Material> material)
	: center(_center), radius(_radius), material_ptr(material) {}

bool Sphere::hit(const Ray& ray, double t_min, double t_max, HitRecord& hit_rec) const {
	Vec3 oc = ray.origin() - center;
	double a = ray.direction().length_squared();
	double half_b = dot(oc, ray.direction());
	double c = oc.length_squared() - radius * radius;
	double d = half_b * half_b - a * c;
	if (d < 0) return false;

	double temp = (-half_b - sqrt(d)) / a;
	if (temp < t_min || temp > t_max) {
		temp = (-half_b + sqrt(d)) / a;
		if (temp < t_min || temp > t_max) {
			return false;
		}
	}

	hit_rec.t = temp;
	hit_rec.point = ray.at(hit_rec.t);
	hit_rec.material_ptr = material_ptr;

	Vec3 outward_normal = (hit_rec.point - center) / radius;
	hit_rec.set_face_normal(ray, outward_normal);

	return true;
}
