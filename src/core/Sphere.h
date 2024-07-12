#ifndef SPHERE_H
#define SPHERE_H


#include "Shape.h"

namespace PathTracer
{

class Sphere : public Shape
{
 public:
    Sphere() : m_center(0, 0, 0), m_radius(-1) {}
    Sphere(const Point3 &center, double radius) : m_center(center), m_radius(radius) {}
    Sphere(const Point3 &&center, double radius) : m_center(center), m_radius(radius) {}

    ~Sphere() override = default;

    std::optional<CollisionRecord> collide(const Ray &r, Interval i) const override;

 private:
    Point3 m_center;
    double m_radius;
};

};


#endif  //  SPHERE_H
