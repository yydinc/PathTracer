#include <array>
#include <functional>

#include "RayCollisionDetectionSystem.h"
#include "../components/TransformComponent.h"

using namespace PathTracer;

using CollisionFunction = std::function<optional<CollisionRecord>(const TransformComponent &,
                                                                  const RayColliderComponent &,
                                                                  const Ray &, const Interval &)>;

static std::array<CollisionFunction, MAX_RAY_COLLIDER_TYPE> s_functionMap;

inline bool isFrontFace(const Ray& r, const Vector3& normal)
{
    return dot(r.direction(), normal) < 0;
}

inline bool isFrontFace(const Ray& r, const Vector3&& normal)
{
    return dot(r.direction(), normal) < 0;
}

optional<CollisionRecord> collideWithSphericalCollider(const TransformComponent &transform,
                                                       const RayColliderComponent &collider,
                                                       const Ray &ray, const Interval &interval)
{
    Vector3 originToCenter = transform.position - ray.origin();
    double a = ray.direction().lengthSquared();
    double h = dot(ray.direction(), originToCenter);
    double c = originToCenter.lengthSquared() - collider.radius*collider.radius;

    double discriminant = h*h - a*c;

    if(discriminant < 0) return {};

    double sqrtDiscriminant = sqrt(discriminant);

    double root = (h - sqrtDiscriminant) / a;

    if(!interval.contains(root))
    {
        root = (h + sqrtDiscriminant) / a;
        if(!interval.contains(root))
        {
            return {};
        }
    }

    Vector3 outwardNormal = (ray.at(root) - transform.position) / collider.radius;

    return CollisionRecord{ray.at(root), outwardNormal, root, isFrontFace(ray, outwardNormal)};
}



void initializeFunctionMap()
{
      //  Add new collision functions if new collider types are added

    s_functionMap[ColliderType::Spherical] = collideWithSphericalCollider;
}

optional<CollisionRecord> collide(const TransformComponent &transformComponent,
                                  const RayColliderComponent &collider,
                                  const Ray &ray, const Interval &interval)
{
    return s_functionMap[collider.type](transformComponent, collider, ray, interval);
}

optional<CollisionRecord> RayCollisionDetectionSystem::collideFirst(const Scene &scene, const Ray &ray, const Interval &interval)
{
    ONCE(initializeFunctionMap);

    CollisionRecord cRec;
    const size_t colliderComponentId = scene.getComponentId<RayColliderComponent>();
    const size_t transformComponentId = scene.getComponentId<TransformComponent>();

    auto *p_colliderStorage = scene.getComponentStorage<RayColliderComponent>();
    auto *p_transformStorage = scene.getComponentStorage<TransformComponent>();
    for(size_t i = 0; i < scene.entityCount(); i++)
    {
        if(!scene.getEntityDescriptor(i).mask.test(colliderComponentId)) continue;

        const auto &collider = p_colliderStorage->getElementAt(i);
        const auto &transform = p_transformStorage->getElementAt(i);
        auto tempRec = collide(transform, collider, ray, interval);
        if(tempRec)
        {
            cRec = (cRec.t < tempRec->t) ? cRec : tempRec.value();
        }
    }

    return (cRec.t < std::numeric_limits<double>::max()) ? cRec : optional<CollisionRecord>{} ;
}

Color RayCollisionDetectionSystem::rayColor(const Scene &scene, const Ray &ray)
{
    auto cRec = RayCollisionDetectionSystem::collideFirst(scene, ray, {-infinity, infinity});
    if (cRec) {
        return 0.5 * Color(cRec->outwardNormal.x + 1, cRec->outwardNormal.y + 1, cRec->outwardNormal.z + 1);
    }

    Vector3 unitDirection = unitVector(ray.direction());
    double a = 0.5 * (unitDirection.y + 1.0);
    return Color(1.0, 1.0, 1.0) * (1.0 - a) + Color(0.5, 0.7, 1.0) * a;
}
