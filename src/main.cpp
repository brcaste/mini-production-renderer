#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <limits>
#include <memory>
#include <filesystem>

#include "../include/Vec3.h"
#include "../include/Ray.h"
#include "../include/Camera.h"
#include "../include/HittableList.h"
#include "../include/Sphere.h"
#include "../include/Hittable.h"


using namespace std;
namespace fs = filesystem;
double hit_sphere(const Vec3& center, double radius, const Ray& r) {
    Vec3 oc = r.origin - center;
    double a = dot(r.direction, r.direction);
    double b = 2.0 * dot(oc, r.direction);
    double c = dot(oc, oc) - radius * radius;
    double discriminant = b*b - 4*a*c;
    if (discriminant < 0) return -1.0;
    return (-b - std::sqrt(discriminant)) / (2.0 * a);
}

Vec3 ray_color(const Ray& r) {
    double t;

    // small sphere
    t = hit_sphere(Vec3(0, 0, -1), 0.5, r);
    if (t > 0.0) {
        Vec3 n = normalize(r.at(t) - Vec3(0, 0, -1));
        return 0.5 * Vec3(n.x + 1, n.y + 1, n.z + 1);
    }

    // ground
    t = hit_sphere(Vec3(0, -100.5, -1), 100.0, r);
    if (t > 0.0) {
        Vec3 n = normalize(r.at(t) - Vec3(0, -100.5, -1));
        return 0.5 * Vec3(n.x + 1, n.y + 1, n.z + 1);
    }

    Vec3 unit_dir = normalize(r.direction);
    double a = 0.5 * (unit_dir.y + 1.0);
    return (1.0 - a) * Vec3(1.0, 1.0, 1.0) + a * Vec3(0.5, 0.7, 1.0);
}


// Vec3 ray_color(const Ray& r, const Hittable& world) {
//     HitRecord rec;
//
//     if (world.hit(r,0.001, numeric_limits<double>::infinity(), rec))
//     {
//         return 0.5 * Vec3(rec.normal.x + 1, rec.normal.y + 1, rec.normal.z + 1);
//     }
//
//     Vec3 unit_dir = normalize(r.direction);
//     double a = 0.5 * (unit_dir.y + 1.0);
//     return (1.0 - a) * Vec3(1.0, 1.0, 1.0) + a * Vec3(0.5, 0.7, 1.0);
// }

static int to_byte(double x){
    // clamp to [0, 0.999] then scale
    if (x < 0) x = 0;
    if (x > 0.999) x = 0.999;
    return static_cast<int>(256*x);
}

int main()
{
    const int WIDTH = 400;
    const int HEIGHT = 225;
    Camera cam(double(WIDTH) / HEIGHT);
    const fs::path outPath = "output/sphere2.ppm";
    fs::create_directories(outPath.parent_path());

    HittableList world;
    world.add(make_shared<Sphere>(Vec3(0,0,-1), 0.5));
    world.add(make_shared<Sphere>(Vec3(0,-100.5,-1), 100.0));

    //PPM output header;
    ofstream out(outPath, ios::binary);
    if (!out)
    {
        cerr << "Error opening output file " << outPath << endl;
        return 1;
    }

    out << "P3\n" << WIDTH << ' ' << HEIGHT << "\n255\n";
    for (int j = HEIGHT -1; j >= 0; --j){
        for (int i = 0; i < WIDTH; ++i){
            double u = double(i) / (WIDTH - 1);
            double v = double(j) / (HEIGHT - 1);
            Ray r = cam.get_ray(u, v);
            Vec3 color = ray_color(r);
            out << to_byte(color.x) << ' '
            << to_byte(color.y) << ' '
            << to_byte(color.z) << '\n';
        }
    }
    cout << "Wrote " << outPath << "\n";
    return 0;
}