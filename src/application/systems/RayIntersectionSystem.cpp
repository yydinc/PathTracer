#include <array>
#include <functional>

#include "RayIntersectionSystem.h"
#include "TransformComponent.h"
#include "RayScatteringSystem.h"
#include "Random.h"

using namespace PathTracer;

using RayIntersectionFunction = optional<RayIntersectionRecord>(const TransformComponent &,
                                                          const RayColliderComponent &,
                                                          const Ray &, const Interval &);

std::array<RayIntersectionFunction*, MAX_RAY_COLLIDER_TYPE> rayIntersectionFunctionMap;

inline bool isFrontFace(const Ray& r, const Vector3& normal)
{
    return dot(r.direction(), normal) < 0;
}

inline bool isFrontFace(const Ray& r, const Vector3&& normal)
{
    return dot(r.direction(), normal) < 0;
}

void initializeFunctionMap()
{
      //  Add new collision functions if new collider types are added

    rayIntersectionFunctionMap[ColliderType::Spherical] = [](const TransformComponent &transform,
                                                       const RayColliderComponent &collider,
                                                       const Ray &ray, const Interval &interval){
        Vector3 originToCenter = transform.position - ray.origin();
        double a = ray.direction().lengthSquared();
        double h = dot(ray.direction(), originToCenter);
        double c = originToCenter.lengthSquared() - collider.radius*collider.radius;

        double discriminant = h*h - a*c;

        if(discriminant < 0) return optional<RayIntersectionRecord>{};

        double sqrtDiscriminant = sqrt(discriminant);

        double root = (h - sqrtDiscriminant) / a;

        if(!interval.contains(root))
        {
            root = (h + sqrtDiscriminant) / a;
            if(!interval.contains(root))
            {
                return optional<RayIntersectionRecord>{};
            }
        }

        Vector3 outwardNormal = (ray.at(root) - transform.position) / collider.radius;

        bool frontFace = isFrontFace(ray, outwardNormal);

        return std::optional<RayIntersectionRecord>{RayIntersectionRecord{ray.at(root), frontFace ? outwardNormal : -1*outwardNormal, root, frontFace}};
    };
}

optional<RayIntersectionRecord> collide(const TransformComponent &transformComponent,
                                        const RayColliderComponent &collider,
                                        const Ray &ray, const Interval &interval)
{
    return rayIntersectionFunctionMap[collider.type](transformComponent, collider, ray, interval);
}

optional<RayIntersectionRecord> RayIntersectionSystem::collideFirst(const Scene &scene, const Ray &ray, const Interval &interval)
{
    ONCE(initializeFunctionMap);

    RayIntersectionRecord cRec;
    const size_t colliderComponentId = scene.getComponentId<RayColliderComponent>();

    auto *p_colliderStorage = scene.getComponentStorage<RayColliderComponent>();
    auto *p_transformStorage = scene.getComponentStorage<TransformComponent>();
    auto *p_materialStorage = scene.getComponentStorage<MaterialComponent>();
    for(size_t i = 0; i < scene.entityCount(); i++)
    {
        if(!scene.getEntityDescriptor(i).mask.test(colliderComponentId)) continue;

        const auto &collider = p_colliderStorage->getElementAt(i);
        const auto &transform = p_transformStorage->getElementAt(i);
        auto tempRec = collide(transform, collider, ray, interval);
        if(tempRec)
        {
            tempRec->material = p_materialStorage->getElementAt(i);
            cRec = (cRec.t < tempRec->t) ? cRec : tempRec.value();
        }
    }

    return (cRec.t < std::numeric_limits<double>::max()) ? cRec : optional<RayIntersectionRecord>{} ;
}

Color RayIntersectionSystem::rayColor(const Scene &scene, const Ray &ray, int depth)
{
    if(depth == 0) return {0};
    auto cRec = RayIntersectionSystem::collideFirst(scene, ray, {0.001, infinity});
    if (cRec) {
        return cRec->material.albedo * rayColor(scene, RayScatteringSystem::scatter(ray, cRec.value()), depth - 1);
    }

    Vector3 unitDirection = unitVector(ray.direction());
    double a = 0.5 * (unitDirection.y + 1.0);
    return Color(1.0, 1.0, 1.0) * (1.0 - a) + Color(0.5, 0.7, 1.0) * a;
}
