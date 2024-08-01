#ifndef RAY_COLLISION_DETECTION_SYSTEM_H
#define RAY_COLLISION_DETECTION_SYSTEM_H


#include <optional>

#include "../Scene.h"
#include "../../core/Color.h"
#include "../../core/Ray.h"
#include "../../core/CollisionRecord.h"
#include "../../core/Interval.h"

namespace PathTracer::RayCollisionDetectionSystem
{

Color rayColor(const Scene &scene, const Ray &ray);

optional<CollisionRecord> collideFirst(const Scene &scene, const Ray &ray, const Interval &interval);

};

#endif  //  RAY_COLLISION_DETECTION_SYSTEM_H
