#pragma once
#include "../core/Ray.h"
#include "../core/Vec3.h"
#include <memory>

class Material;

struct HitRecord {
  Vec3 p;   //hit point
  Vec3 normal; //surface normal
  double t;   //ray parameter at hit
  bool front_face;  //where we hit outside surface
  std::shared_ptr<Material> mat;

  void set_face_normal(const Ray& r, const Vec3& outward_normal)
  {
    front_face = dot(r.direction, outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
  }
};

class Hittable {
public:
  virtual ~Hittable() = default;

  // return true if ray hits objects between t_min and t_max
  virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
};