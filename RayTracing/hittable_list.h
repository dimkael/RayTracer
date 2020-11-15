#pragma once

#include <memory>
#include <vector>
#include "hittable.h"

class HittableList : public Hittable {
public:
	HittableList();
	HittableList(std::shared_ptr<Hittable> object);

	void clear();
	void add(std::shared_ptr<Hittable> object);

	virtual bool hit(const Ray& ray, double t_min, double t_max, HitRecord& hit_rec) const override;

public:
	std::vector<std::shared_ptr<Hittable>> objects;
};