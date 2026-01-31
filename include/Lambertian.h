#pragma once
#include "Material.h"
#include <cmath>

inline Vec3 random_in_unit_sphere()
{
    while (true)
    {
        Vec3 p(2*random_double()-1, 2*random_double()-1, 2*random_double()-1);
        if (p.length2() >= 1) continue;
        return p;
    }
}

inline Vec3 random_unit_vector()
{
    return normalize(random_in_unit_sphere());
}

class Lambertian : public Material
{
public:
    explicit Lambertian(const Vec3& albedo_) : albedo(albedo_) {}

    bool scatter(const Ray&, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const override
    {
        Vec3 scatter_dir = rec.normal + random_unit_vector();
        // catch degenerate direction
        if (scatter_dir.length2() < 1e-12) scatter_dir = rec.normal;

        scattered = Ray(rec.p, scatter_dir);
        attenuation = albedo;
        return true;
    }
private:
    Vec3 albedo;
};
