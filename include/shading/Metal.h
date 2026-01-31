#pragma once
#include "Material.h"
#include <cmath>

#include "Lambertian.h"

inline Vec3 reflect(const Vec3& v, const Vec3& n)
{
    return v - 2 * dot(v,n) * n;
}

class Metal : public Material
{
public:
    Metal(const Vec3& albedo_, double fuzz_): albedo(albedo_), fuzz(fuzz_ < 1 ? fuzz : 1){}

    bool scatter(const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const override
    {
        Vec3 reflected = reflect(normalize(r_in.direction), rec.normal);
        scattered = Ray(rec.p, reflected + fuzz * random_in_unit_sphere());
        attenuation = albedo;
        return (dot(scattered.direction, rec.normal) > 0 );
    }
private:
    Vec3 albedo;
    double fuzz;
};
