#ifndef RAY_COLLIDER_COMPONENT_H
#define RAY_COLLIDER_COMPONENT_H


#include "../../Shape.h"
#include "../../Sphere.h"

namespace PathTracer
{

struct SphericalRayColliderComponent
{
    Sphere sphere;
};

};

#endif  //  RAY_COLLIDER_COMPONENT_H
