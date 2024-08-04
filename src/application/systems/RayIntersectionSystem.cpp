#include <array>
#include <functional>

#include "RayIntersectionSystem.h"
#include "TransformComponent.h"
#include "Random.h"

using namespace PathTracer;

using CollisionFunction = optional<CollisionRecord>(const TransformComponent &,
                                                    const RayColliderComponent &,
                                                    const Ray &, const Interval &);

static std::array<CollisionFunction*, MAX_RAY_COLLIDER_TYPE> s_functionMap;

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

    s_functionMap[ColliderType::Spherical] = [](const TransformComponent &transform,
                                                       const RayColliderComponent &collider,
                                                       const Ray &ray, const Interval &interval){
        Vector3 originToCenter = transform.position - ray.origin();
        double a = ray.direction().lengthSquared();
        double h = dot(ray.direction(), originToCenter);
        double c = originToCenter.lengthSquared() - collider.radius*collider.radius;

        double discriminant = h*h - a*c;

        if(discriminant < 0) return optional<CollisionRecord>{};

        double sqrtDiscriminant = sqrt(discriminant);

        double root = (h - sqrtDiscriminant) / a;

        if(!interval.contains(root))
        {
            root = (h + sqrtDiscriminant) / a;
            if(!interval.contains(root))
            {
                return optional<CollisionRecord>{};
            }
        }

        Vector3 outwardNormal = (ray.at(root) - transform.position) / collider.radius;

        return std::optional<CollisionRecord>{CollisionRecord{ray.at(root), outwardNormal, root, isFrontFace(ray, outwardNormal)}};
    };
}

optional<CollisionRecord> collide(const TransformComponent &transformComponent,
                                  const RayColliderComponent &collider,
                                  const Ray &ray, const Interval &interval)
{
    return (*s_functionMap[collider.type])(transformComponent, collider, ray, interval);
}

optional<CollisionRecord> RayIntersectionSystem::collideFirst(const Scene &scene, const Ray &ray, const Interval &interval)
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

Color RayIntersectionSystem::rayColor(const Scene &scene, const Ray &ray, int depth)
{
    if(depth == 0) return {0};
    auto cRec = RayIntersectionSystem::collideFirst(scene, ray, {0.001, infinity});
    if (cRec) {
        Vector3 randomUnitV = randomUnitVector();
        randomUnitV = dot(cRec->outwardNormal, randomUnitV) > 0 ? randomUnitV : -1 * randomUnitV;
        return 0.5 * rayColor(scene, {cRec->point, randomUnitV}, depth-1);
    }

    Vector3 unitDirection = unitVector(ray.direction());
    double a = 0.5 * (unitDirection.y + 1.0);
    return Color(1.0, 1.0, 1.0) * (1.0 - a) + Color(0.5, 0.7, 1.0) * a;
}
