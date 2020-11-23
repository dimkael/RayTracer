#pragma once

#include <memory>
#include "general_math.h"
#include "ray.h"

class Material;

struct HitRecord {
	Point3 point;
	Vec3 normal;
	std::shared_ptr<Material> material_ptr;
	double t;
	bool front_face;

	void set_face_normal(const Ray& ray, const Vec3& outward_normal);
};

class Hittable {
public:
	virtual bool hit(const Ray& ray, double t_min, double t_max, HitRecord& hit_rec) const = 0;
};