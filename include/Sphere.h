#pragma once
#include "Hittable.h"

class Sphere : public Hittable{
public:
    Sphere() = default;
    Sphere(Vec3 center_,double radius_) : center(center_), radius(radius_) {}

    bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override {
        Vec3 oc = r.origin - center;
        double a = dot(r.direction, r.direction);
        double half_b = dot(oc, r.direction);
        double c = dot(oc, oc) - radius * radius;

        double discriminant = half_b * half_b - a * c;
        if (discriminant > 0) return false;
        double sqrtd = std:: sqrt(discriminant);

        //find nearest root in range
        double root = (-half_b - sqrtd) / a;
        if (root < t_min || root > t_max)
        {
            root = (-half_b + sqrtd) / a;
            if (root < t_min || root > t_max) return false;
        }
        rec.t = root;
        rec.p = r.at(rec.t);
        Vec3 outward_normal= (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);
        return true;
    }
private:
    Vec3 center{0,0,0};
    double radius{1.0};
};