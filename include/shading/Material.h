#pragma once
#include "../core/Ray.h"
#include "../core/Vec3.h"
#include "../geometry/Hittable.h"

class Material
{
public:
    virtual ~Material()= default;
    virtual bool scatter(
        const Ray& r_in,
        const HitRecord& rec,
        Vec3& attenuation,
        Ray& scattered
        )const = 0;
};