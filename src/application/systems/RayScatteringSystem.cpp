#include <array>

#include "RayScatteringSystem.h"
#include "Random.h"
#include "Constants.h"
#include "Scene.h"
#include "MaterialComponent.h"

using namespace PathTracer;

using RayScatterFunction = Ray(const Ray &ray, const RayIntersectionRecord &intersectionRecord);

std::array<RayScatterFunction*, MAX_MATERIAL_TYPE> rayScatterFunctionMap;

void init()
{
    rayScatterFunctionMap[MaterialType::Simple] = [](const Ray &ray, const RayIntersectionRecord &intersectionRecord)
            {
                return Ray{intersectionRecord.point, randomUnitVectorOnHemisphere(intersectionRecord.normal)};
            };

    rayScatterFunctionMap[MaterialType::TrueLambertian] = [](const Ray &ray, const RayIntersectionRecord &intersectionRecord)
            {
                return Ray{intersectionRecord.point, randomUnitVector() + intersectionRecord.normal};}
            ;

    rayScatterFunctionMap[MaterialType::Metal] = [](const Ray &ray, const RayIntersectionRecord &intersectionRecord)
            {
                Vector3 reflected = mirror(ray.direction(), intersectionRecord.normal);
                reflected = unitVector(reflected) + (intersectionRecord.material.fuzz * randomUnitVector());
//                reflected = (dot(reflected, intersectionRecord.normal) > 0) ? reflected: Vector3{0};
                return Ray{intersectionRecord.point, reflected};
            };

    rayScatterFunctionMap[MaterialType::Dielectrics] = [](const Ray &ray, const RayIntersectionRecord &intersectionRecord)
            {
                double refractionIndex = intersectionRecord.frontFace ? (1.0/intersectionRecord.material.refractionIndex) : intersectionRecord.material.refractionIndex;

                Vector3 unitDirection = unitVector(ray.direction());

                double cosTheta = dot(-1*unitDirection, intersectionRecord.normal);
                double sinTheta = std::sqrt(1.0 - cosTheta*cosTheta);

                        // Use Schlick's approximation for reflectance.
                auto r0 = (1 - refractionIndex) / (1 + refractionIndex);
                r0 = r0*r0;
                double reflectance = r0 + (1-r0)*std::pow((1 - cosTheta),5);

                bool mirrorAngle = (refractionIndex * sinTheta > 1.0) || (reflectance > randomDouble());


                Vector3 direction = mirrorAngle ? mirror(unitDirection, intersectionRecord.normal)
                                                : refract(unitDirection, intersectionRecord.normal, refractionIndex);

                return Ray{intersectionRecord.point, direction};
            };
}

Ray RayScatteringSystem::scatter(const Ray &ray, const RayIntersectionRecord &intersectionRecord)
{
    ONCE(init);
    return rayScatterFunctionMap[intersectionRecord.material.materialType](ray, intersectionRecord);
}