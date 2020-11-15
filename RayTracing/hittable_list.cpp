#include "hittable_list.h"

HittableList::HittableList() {}
HittableList::HittableList(std::shared_ptr<Hittable> object) {
	add(object);
}

void HittableList::clear() {
	objects.clear();
}
void HittableList::add(std::shared_ptr<Hittable> object) {
	objects.push_back(object);
}

bool HittableList::hit(const Ray& ray, double t_min, double t_max, HitRecord& hit_rec) const {
	HitRecord temp_rec;
	bool has_hit = false;
	double t_closest = t_max;

	for (const auto& obj : objects) {
		if (obj->hit(ray, t_min, t_closest, temp_rec)) {
			has_hit = true;
			t_closest = temp_rec.t;
			hit_rec = temp_rec;
		}
	}

	return has_hit;
}