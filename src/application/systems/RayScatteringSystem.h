#ifndef RAY_SCATTERING_SYSTEM_H
#define RAY_SCATTERING_SYSTEM_H


#include "RayIntersectionRecord.h"
#include "Ray.h"

namespace PathTracer::RayScatteringSystem
{

Ray scatter(const Ray &ray, const RayIntersectionRecord &intersectionRecord);

};

#endif  //  RAY_SCATTERING_SYSTEM_H
