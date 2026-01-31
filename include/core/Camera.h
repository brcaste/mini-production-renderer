#pragma once

#include "Ray.h"
#include "Vec3.h"

class Camera {
public:
    Camera(
        double aspect_ratio = 16.0 / 9.0,
        double view_height = 2.0,
        double focal_length = 1.0
    );

    Ray get_ray(double u, double v) const;
private:
    Vec3 origin;
    Vec3 horizontal;
    Vec3 vertical;
    Vec3 lower_left_corner;
};