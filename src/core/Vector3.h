#ifndef VECTOR3_H
#define VECTOR3_H


#include <iostream>

namespace PathTracer
{

class Vector3
{
 public:
    constexpr Vector3() : x(0), y(0), z(0) {}
    constexpr Vector3(double m) : x(m), y(m), z(m) {}
    constexpr Vector3(double x, double y, double z) : x(x), y(y), z(z) {}
    constexpr Vector3(const Vector3 &other)  : x(other.x), y(other.y), z(other.z) {}

    void add(const Vector3 &other);
    void subtract(const Vector3 &other);
    void multiply(const Vector3 &other);
    void divide(const Vector3 &other);

    void multiply(double t);
    void divide(double t);

    Vector3 &operator+=(const Vector3 &other);
    Vector3 &operator-=(const Vector3 &other);
    Vector3 &operator*=(const Vector3 &other);
    Vector3 &operator/=(const Vector3 &other);
    Vector3 &operator*=(double t);
    Vector3 &operator/=(double t);
    double length() const;
    double lengthSquared() const;

 public:
    union
    {
        struct { double x, y, z; };
        struct { double r, g, b; };
    };

};

inline Vector3 operator+(const Vector3 &v, const Vector3 &w)
{
    return {v.x+w.x, v.y+w.y, v.z+w.z};
}

inline Vector3 operator-(const Vector3 &v, const Vector3 &w)
{
    return {v.x-w.x, v.y-w.y, v.z-w.z};
}

inline Vector3 operator*(const Vector3 &v, const Vector3 &w)
{
    return {v.x*w.x, v.y*w.y, v.z*w.z};
}

inline Vector3 operator/(const Vector3 &v, const Vector3 &w)
{
    return {v.x/w.x, v.y/w.y, v.z/w.z};
}

inline Vector3 operator*(const Vector3 &v, double t)
{
    return {v.x*t, v.y*t, v.z*t};
}

inline Vector3 operator*(double t, const Vector3 &v)
{
    return v*t;
}

inline Vector3 operator/(const Vector3 &v, double t)
{
    return v*(1/t);
}

inline Vector3 unitVector(const Vector3 &v)
{
    return v/v.length();
}

inline double dot(const Vector3 &v, const Vector3 &w)
{
    return v.x*w.x + v.y*w.y + v.z*w.z;
}

inline Vector3 cross(const Vector3 &v, const Vector3 &w)
{
    return {v.y*w.z - v.z*w.y,
            v.z*w.x - v.x*w.z,
            v.x*w.y - v.y*w.x};
}

inline std::ostream &operator<<(std::ostream &out, const Vector3 &v)
{
    return out << "<" << v.x << ", " << v.y << ", " << v.z << ">";
}

};


#endif  //  VECTOR3_H