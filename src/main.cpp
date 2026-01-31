#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

#include "Vec3.h"
#include "Ray.h"
#include "../include/Camera.h"
#include "../include/Vec3.h"


using namespace std;

double hit_sphere(const Vec3& center, double radius, const Ray& r)
{
    Vec3 oc = r.origin - center;
    double a = dot(r.direction, r.direction);
    double b = 2.0 * dot(oc, r.direction);
    double c = dot(oc, oc) - radius * radius;
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) return -1.0;
    return (-b - sqrt(discriminant)) / (2 * a);
}
Vec3 ray_color(const Ray& r) {
    //small sphere
    double t = hit_sphere(Vec3(0,0,-1), 0.5, r);
    if (t < 0.0) {
        // simple normal-based shading
        Vec3 n = normalize(r.at(t) - Vec3(0,0,-1)); //normal at hit point
        return 0.5 * Vec3(n.x + 1, n.y + 1, n.z + 1); //map [-1,1] to [0,1]
    }

    //ground
    t = hit_sphere(Vec3(0,-100.5,-1), 100.0, r);
    if (t < 0.0)
    {
        Vec3 n = normalize(r.at(t) - Vec3(0,-100.5,-1));
        return 0.5 * Vec3(n.x + 1, n.y + 1, n.z + 1);
    }

    Vec3 unit_dir = normalize(r.direction);
    double a = 0.5 * (unit_dir.y + 1.0);
    return (1.0 - a) * Vec3(1.0, 1.0, 1.0) + a * Vec3(0.5, 0.7, 1.0);
}

static int to_byte(double x){
    // clamp to [0, 0.999] then scale
    if (x < 0) x = 0;
    if (x > 0.999) x = 0.999;
    return static_cast<int>(256*x);
}

int main()
{
    const int WIDTH = 400;
    const int HEIGHT = 255;

    Camera cam(double(WIDTH) / HEIGHT);

    const string outPath = string(PROJECT_ROOT_DIR) + "/build/bin/Release/output/sphere.ppm";


    ofstream out(outPath, ios::out | ios::trunc);
    if (!out)
    {
        cerr << "Error opening output file " << outPath << endl;
        return 1;
    }
    // //Camera (Simple pinhole)
    // const double viewport_height = 2.0;
    // const double viewport_width = viewport_height * (double(WIDTH) / HEIGHT);
    // const double focal_length = 1.0;
    //
    // Vec3 origin(0, 0, 0);
    // Vec3 horizontal(viewport_width, 0, 0);
    // Vec3 vertical(0, viewport_height, 0);
    // Vec3 lower_left = origin - horizontal/2 - vertical/2- Vec3(0, 0, focal_length);
    //

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