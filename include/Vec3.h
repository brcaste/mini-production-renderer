#pragma once
#include <cmath>
#include <ostream>

struct Vec3
{
    double x{0}, y{0}, z{0};

    Vec3() = default;
    Vec3(const double _x, const double _y, const double _z): x(_x), y(_y), z(_z){}

    Vec3 operator-() const { return Vec3(-x, -y, -z);};
    Vec3& operator+=(const Vec3& rhs) {x+=rhs.x; y+=rhs.y; z+=rhs.z; return *this;}
    Vec3& operator-=(const Vec3& rhs) {x-=rhs.x; y-=rhs.y; z-=rhs.z; return *this;}
    Vec3& operator*=(double t) {x*=t; y*=t; z*=t; return *this;}
    Vec3& operator/=(double t) {x/=t;y/=t; z/=t; return *this;}

    [[nodiscard]] double length() const {return sqrt(x*x+y*y+z*z);}
    [[nodiscard]] double length2() const {return x*x+y*y+z*z;}
};
inline Vec3 operator+(Vec3 a, const Vec3& b) { return a += b; }
inline Vec3 operator-(Vec3 a, const Vec3& b) { return a -= b; }
inline Vec3 operator*(Vec3 v, double t)      { return v *= t; }
inline Vec3 operator*(double t, Vec3 v)      { return v *= t; }
inline Vec3 operator/(Vec3 v, double t)      { return v /= t; }

inline double dot(const Vec3& a, const Vec3& b){
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

inline Vec3 normalize(const Vec3& v){
    return v / v.length();
}

inline std::ostream& operator<<(std::ostream& os, const Vec3& v)
{
    return os << v.x << " " << v.y << " " << v.z;
}
