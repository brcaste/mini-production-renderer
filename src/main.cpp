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

Vec3 ray_color(const Ray& r, const Hittable& world) {
    HitRecord rec;
    if (world.hit(r, 0.001, std::numeric_limits<double>::infinity(), rec)) {
        return 0.5 * Vec3(rec.normal.x + 1.0, rec.normal.y + 1.0, rec.normal.z + 1.0);
    }

    Vec3 unit_dir = normalize(r.direction);
    double a = 0.5 * (unit_dir.y + 1.0);
    return (1.0 - a) * Vec3(1.0, 1.0, 1.0) + a * Vec3(0.5, 0.7, 1.0);
}

static double clamp01(double x)
{
    if (!isfinite(x)) return 0.0;
    if (x < 0.0) return 0.0;
    if (x > 0.999) return 0.999;
    return x;
}

static int to_byte(double x){
    x = clamp01(x);
    return static_cast<int>(256.0*x);
}

static void write_color(ostream& out, const Vec3& pixel_color, int samples_per_pixel)
{
    //Average
    double scale = 1.0 / samples_per_pixel;
    double r = pixel_color.x * scale;
    double g = pixel_color.y * scale;
    double b = pixel_color.z * scale;

    //gamma correction (gamma=2.0)
    r = sqrt(clamp01(r));
    g = sqrt(clamp01(g));
    b = sqrt(clamp01(b));
    out << to_byte(r) << ' ' << to_byte(g) << ' ' << to_byte(b) << endl;
}

int main()
{
    const int WIDTH = 400;
    const int HEIGHT = 225;
    const int SAMPLES_PER_PIXEL = 10;

    Camera cam(double(WIDTH) / HEIGHT);
    const fs::path outPath = "output/sphere_with_aliasing.ppm";
    fs::create_directories(outPath.parent_path());

    HittableList world;
    world.add(make_shared<Sphere>(Vec3(0,0,-1), 0.5));
    world.add(make_shared<Sphere>(Vec3(0,-100.5,-1), 100.0));
    //PPM output header;
    ofstream out(outPath);
    if (!out)
    {
        cerr << "Error opening output file " << outPath << endl;
        return 1;
    }

    out << "P3\n" << WIDTH << ' ' << HEIGHT << "\n255\n";
    for (int j = HEIGHT -1; j >= 0; --j){
        for (int i = 0; i < WIDTH; ++i){
            Vec3 pixel_color = Vec3(0, 0, 0);
            for (int s = 0; s < SAMPLES_PER_PIXEL; ++s)
            {
                double u = (i + random_double()) / (WIDTH - 1);
                double v = (j + random_double()) / (HEIGHT - 1);
                Ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r,world);
            }

            write_color(out, pixel_color, SAMPLES_PER_PIXEL);
        }
    }
    cout << "Wrote " << outPath << "\n";
    return 0;
}