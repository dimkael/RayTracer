#pragma once

#include "hittable.h"
#include "vec3.h"

class Sphere : public Hittable {
public:
	Sphere();
	Sphere(Point3 _center, double _radius, std::shared_ptr<Material> material);

	virtual bool hit(const Ray& ray, double t_min, double t_max, HitRecord& hit_rec) const override;

public:
	Point3 center;
	double radius;
	std::shared_ptr<Material> material_ptr;
};