#include "Camera.h"
#include "Random.h"

PathTracer::Color PathTracer::Camera::rayColor(const PathTracer::Scene &scene, const PathTracer::Ray &ray) const
{
    auto cRec = scene.collideFirst(ray, {-infinity, infinity});
    if (cRec)
    {
        return 0.5*Color(cRec->outwardNormal.x+1, cRec->outwardNormal.y+1, cRec->outwardNormal.z+1);
    }

    Vector3 unitDirection = unitVector(ray.direction());
    double  a = 0.5*(unitDirection.y + 1.0);
    return Color(1.0, 1.0, 1.0)*(1.0-a) + Color(0.5, 0.7, 1.0)*a;
}


void PathTracer::Camera::render(const PathTracer::Scene &scene) const
{
    std::cout << "P3\n" << m_imageWidth << ' ' << m_imageHeight << "\n255\n";

    for (int j = 0; j < m_imageHeight; j++)
    {
        std::clog << "\rScanlines Remaining: " << (m_imageHeight - j) << ' ' << std::flush;
        for (int i = 0; i < m_imageWidth; i++)
        {
            Color pixelColor{0};

            for(int sample = 0; sample < m_samplesPerPixel; sample++)
            {
                Point3 pixelLocation = m_pixel00Location + m_deltaU*(i + randomDouble({-0.5, 0.5})) + m_deltaV*(j + randomDouble({-0.5, 0.5}));
                Vector3 rayDirection = pixelLocation - m_location;

                Ray r(m_location, rayDirection);
                pixelColor += rayColor(scene, r);
            }

            writeColor(pixelColor * m_pixelColorScaler);
        }
    }
    std::clog << "\rDone.               \n";

}