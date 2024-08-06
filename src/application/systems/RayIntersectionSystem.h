#ifndef RAY_COLLISION_DETECTION_SYSTEM_H
#define RAY_COLLISION_DETECTION_SYSTEM_H


#include <optional>

#include "Scene.h"
#include "Color.h"
#include "Ray.h"
#include "RayIntersectionRecord.h"
#include "Interval.h"

namespace PathTracer::RayIntersectionSystem
{

Color rayColor(const Scene &scene, const Ray &ray, int depth);

optional<RayIntersectionRecord> collideFirst(const Scene &scene, const Ray &ray, const Interval &interval);

};

#endif  //  RAY_COLLISION_DETECTION_SYSTEM_H
