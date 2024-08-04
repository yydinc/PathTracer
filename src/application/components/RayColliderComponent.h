#ifndef RAY_COLLIDER_COMPONENT_H
#define RAY_COLLIDER_COMPONENT_H


namespace PathTracer
{

enum ColliderType { Spherical };

struct RayColliderComponent
{
    ColliderType type;
    double radius;
};

};

#endif  //  RAY_COLLIDER_COMPONENT_H
