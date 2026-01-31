#pragma once
#include "Vec3.h"
struct Ray
{
    Vec3 origin;
    Vec3 direction;

    Ray() = default;
    Ray(const Vec3& o, const Vec3& d) : origin(o), direction(d) {}

    [[nodiscard]] Vec3 at(double t) const { return origin + t * direction; }
};