#include "Sphere.h"

namespace PathTracer
{

std::optional<CollisionRecord> Sphere::collide(const Ray &r, Interval i) const
{
    Vector3 originToCenter = m_center - r.origin();
    double a = r.direction().lengthSquared();
    double h = dot(r.direction(), originToCenter);
    double c = originToCenter.lengthSquared() - m_radius*m_radius;

    double discriminant = h*h - a*c;

    if(discriminant < 0) return {};

    double sqrtDiscriminant = sqrt(discriminant);

    double root = (h - sqrtDiscriminant) / a;

    if(!i.contains(root))
    {
        root = (h + sqrtDiscriminant) / a;
        if(!i.contains(root))
        {
            return {};
        }
    }

    Vector3 outwardNormal = (r.at(root) - m_center) / m_radius;

    return CollisionRecord{r.at(root), outwardNormal, root, isFrontFace(r, outwardNormal)};
}

};