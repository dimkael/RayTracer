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


Metal::Metal(const Color& _color, double fuzz) : albedo(_color), fuzziness(fuzz < 1 ? fuzz : 1) {}

bool Metal::scatter(const Ray& ray_in, const HitRecord& hit_rec, Color& attenuation, Ray& scattered) const {
	Vec3 reflected = reflect(unit_vector(ray_in.direction()), hit_rec.normal);
	scattered = Ray(hit_rec.point, reflected + fuzziness * unit_sphere_rand());
	attenuation = albedo;

	return dot(scattered.direction(), hit_rec.normal) > 0;
}


Dielectric::Dielectric(double _refraction_index) : refraction_index(_refraction_index) {}

bool Dielectric::scatter(const Ray& ray_in, const HitRecord& hit_rec, Color& attenuation, Ray& scattered) const {
	attenuation = Color(1.0, 1.0, 1.0);
	double refraction_ratio = hit_rec.front_face ? (1.0 / refraction_index) : refraction_index;

	Vec3 unit_direction = unit_vector(ray_in.direction());
	double cos_theta = fmin(dot(-unit_direction, hit_rec.normal), 1.0);
	double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

	bool cannot_refract = refraction_ratio * sin_theta > 1.0;
	Vec3 direction;
	if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double())
		direction = reflect(unit_direction, hit_rec.normal);
	else
		direction = refract(unit_direction, hit_rec.normal, refraction_ratio);

	scattered = Ray(hit_rec.point, direction);

	return true;
}

double Dielectric::reflectance(double cosine, double reflect_index) {
	double r0 = (1.0 - reflect_index) / (1.0 + reflect_index);
	r0 = r0 * r0;

	return r0 + (1.0 - r0) * pow((1.0 - cosine), 5);
}