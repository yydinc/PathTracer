#ifndef SHAPE_H
#define SHAPE_H


#include <optional>

#include "Ray.h"
#include "CollisionRecord.h"
#include "Interval.h"

namespace PathTracer
{

class Shape
{
 public:
    Shape() = default;
    virtual ~Shape() = default;

    virtual std::optional<CollisionRecord> collide(const Ray &r, Interval i) const = 0;
};

inline bool isFrontFace(const Ray& r, const Vector3& normal)
{
    return dot(r.direction(), normal) < 0;
}

inline bool isFrontFace(const Ray& r, const Vector3&& normal)
{
    return dot(r.direction(), normal) < 0;
}

};

#endif  //  SHAPE_H
