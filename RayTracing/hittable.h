#pragma once

#include "ray.h"

struct HitRecord {
	Point3 point;
	Vec3 normal;
	double t;
	bool front_face;

	inline void set_face_normal(const Ray& ray, const Vec3& outward_normal) {
		front_face = dot(ray.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};

class Hittable {
public:
	virtual bool hit(const Ray& ray, double t_min, double t_max, HitRecord& hit_rec) const = 0;
};