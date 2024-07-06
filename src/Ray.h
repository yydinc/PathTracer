#ifndef RAY_H
#define RAY_H


#include "Point3.h"

namespace PathTracer
{

class Ray
{
 public:
    Ray() = default;
    Ray(const Point3 &point, const Vector3 &direction) : m_origin(point), m_direction(direction) {}

    const Point3 &origin() const {return m_origin;}
    const Vector3 &direction() const {return m_direction;}

    Point3 at(double t) const { return m_origin + m_direction*t;}

 private:
    Point3 m_origin;
    Vector3 m_direction;
};

};


#endif  //  RAY_H
