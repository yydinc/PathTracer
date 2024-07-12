#ifndef RAY_COLLIDER_COMPONENT_H
#define RAY_COLLIDER_COMPONENT_H


#include "../../core/Shape.h"
#include "../../core/Sphere.h"

namespace PathTracer
{

struct SphericalRayColliderComponent
{
    Sphere sphere;
};

};

#endif  //  RAY_COLLIDER_COMPONENT_H
