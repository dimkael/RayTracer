#include "material.h"

Lambertian::Lambertian(const Color& _color) : albedo(_color) {}

bool Lambertian::scatter(const Ray& ray_in, const HitRecord& hit_rec, Color& attenuation, Ray& scattered) const {
	//Vec3 scatter_direction = hit_rec.normal + unit_sphere_rand();
	Vec3 scatter_direction = hit_rec.normal + random_unit_vector();
	//Vec3 scatter_direction = hit_rec.normal + hemisphere_rand(hit_rec.normal);
	if (scatter_direction.near_zero())
		scatter_direction = hit_rec.normal;

	scattered = Ray(hit_rec.point, scatter_direction);
	attenuation = albedo;

	return true;
}


Metal::Metal(const Color& _color) : albedo(_color) {}

bool Metal::scatter(const Ray& ray_in, const HitRecord& hit_rec, Color& attenuation, Ray& scattered) const {
	Vec3 reflected = reflect(unit_vector(ray_in.direction()), hit_rec.normal);
	scattered = Ray(hit_rec.point, reflected);
	attenuation = albedo;

	return dot(scattered.direction(), hit_rec.normal) > 0;
}