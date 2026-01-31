#pragma once
#include "Hittable.h"
#include <memory>
#include <vector>

class HittableList : public Hittable {
public:
    void clear() { objects.clear();}

    void add(std::shared_ptr<Hittable> obj){
        objects.push_back(std::move(obj));
    }

    bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec ) const override {
        HitRecord tempRec;
        bool hit_anything = false;
        double closest_so_far = t_max;

        for (const auto& obj : objects){
            if (obj->hit(r, t_min, closest_so_far, tempRec))
            {
                hit_anything = true;
                closest_so_far = tempRec.t;
                rec = tempRec;
            }
        }
        return hit_anything;
    }

private:
    std::vector<std::shared_ptr<Hittable>> objects;
};