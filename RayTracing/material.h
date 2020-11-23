#pragma once

#include "ray.h"
#include "vec3.h"
#include "general_math.h"
#include "hittable.h"

struct HitRecord;

class Material {
public:
	virtual bool scatter(const Ray& ray_in, const HitRecord& hit_rec, Color& attenuation, Ray& scattered) const = 0;
};


class Lambertian : public Material {
public:
	Lambertian(const Color& _albedo);

	bool scatter(const Ray& ray_in, const HitRecord& hit_rec, Color& attenuation, Ray& scattered) const override;

public:
	Color albedo;
};


class Metal : public Material {
public:
	Metal(const Color& _albedo, double _fuzziness);

	bool scatter(const Ray& ray_in, const HitRecord& hit_rec, Color& attenuation, Ray& scattered) const override;

public:
	Color albedo;
	double fuzziness;
};


class Dielectric : public Material {
public:
	Dielectric(double _refraction_index);

	virtual bool scatter(const Ray& ray_in, const HitRecord& hit_rec, Color& attenuation, Ray& scattered) const override;

public:
	double refraction_index;

private:
	// Schlick approximation for reflectance
	static double reflectance(double cosine, double reflect_index);
};