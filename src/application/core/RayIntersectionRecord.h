#ifndef RAY_INTERSECTION_RECORD_H
#define RAY_INTERSECTION_RECORD_H


#include <memory>

#include "Point3.h"
#include "Vector3.h"
#include "Constants.h"
#include "MaterialComponent.h"

namespace PathTracer
{

struct RayIntersectionRecord
{
    Point3 point;
    Vector3 normal;
    double t = infinity;
    bool frontFace;
    MaterialComponent material;
};

};

#endif  //  RAY_INTERSECTION_RECORD_H
