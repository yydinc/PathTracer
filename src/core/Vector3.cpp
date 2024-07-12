#include <cmath>

#include "Vector3.h"

namespace PathTracer
{

void Vector3::add(const Vector3 &other)
{
    x += other.x;
    y += other.y;
    z += other.y;
}

void Vector3::subtract(const Vector3 &other)
{
    x -= other.x;
    y -= other.y;
    z -= other.y;
}

void Vector3::multiply(const Vector3 &other)
{
    x *= other.x;
    y *= other.y;
    z *= other.y;
}

void Vector3::divide(const Vector3 &other)
{
    x /= other.x;
    y /= other.y;
    z /= other.y;
}

void Vector3::multiply(double t)
{
    x *= t;
    y *= t;
    z *= t;
}

void Vector3::divide(double t)
{
    x /= t;
    y /= t;
    z /= t;
}

Vector3 &Vector3::operator*=(double t)
{
    multiply(t);
    return *this;
}

Vector3 &Vector3::operator/=(double t)
{
    divide(t);
    return *this;
}

double Vector3::length() const
{
    return std::sqrt(lengthSquared());
}

double Vector3::lengthSquared() const
{
    return x*x + y*y + z*z;
}

Vector3 &Vector3::operator+=(const Vector3 &other)
{
    add(other);
    return *this;
}

Vector3 &Vector3::operator-=(const Vector3 &other)
{
    subtract(other);
    return *this;
}

Vector3 &Vector3::operator*=(const Vector3 &other)
{
    multiply(other);
    return *this;
}

Vector3 &Vector3::operator/=(const Vector3 &other)
{
    divide(other);
    return *this;
}

};