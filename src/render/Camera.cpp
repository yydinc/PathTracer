#include "Camera.h"
#include "../core/Random.h"
#include "../core/Timer.h"

namespace PathTracer
{

Color Camera::rayColor(const Scene &scene, const Ray &ray) const
{
    auto cRec = scene.collideFirst(ray, {-infinity, infinity});
    if (cRec) {
        return 0.5 * Color(cRec->outwardNormal.x + 1, cRec->outwardNormal.y + 1, cRec->outwardNormal.z + 1);
    }

    Vector3 unitDirection = unitVector(ray.direction());
    double a = 0.5 * (unitDirection.y + 1.0);
    return Color(1.0, 1.0, 1.0) * (1.0 - a) + Color(0.5, 0.7, 1.0) * a;
}


void Camera::render(const Scene &scene) const
{
//    std::cout << "P3\n" << m_imageWidth << ' ' << m_imageHeight << "\n255\n";
    Timer t;
    long long int totalTime = 0;
    for (int j = 0; j < m_imageHeight; j++) {
//        std::clog << "\rScanlines Remaining: " << (m_imageHeight - j) << ' ' << std::flush;
        for (int i = 0; i < m_imageWidth; i++) {
            Color pixelColor{0};

            t.start();

            for (int sample = 0; sample < m_samplesPerPixel; sample++) {
                Point3 pixelLocation = m_pixel00Location + m_deltaU * (i + randomDouble({-0.5, 0.5})) +
                                       m_deltaV * (j + randomDouble({-0.5, 0.5}));
                Vector3 rayDirection = pixelLocation - m_location;

                Ray r(m_location, rayDirection);
                pixelColor += rayColor(scene, r);
            }

            t.stop();
            totalTime += t.durationMicroSec();
            std::cout << "\r( i: " << i << ", j: " << j << ") - " << t.durationMiliSec() << "ms (" << t.durationMicroSec() << " µs)" << std::flush;

//            writeColor(pixelColor * m_pixelColorScaler);
        }
    }

    std::clog << "\rAverage time: " << (totalTime / (m_imageHeight * m_imageWidth * m_samplesPerPixel)) * 0.001 << "ms\n";
}

void Camera::initialize()
{
    m_imageHeight = static_cast<int>(m_imageWidth/m_aspectRatio);

    m_viewportWidth = m_viewportHeight * (static_cast<double>(m_imageWidth)/m_imageHeight);

    m_pixelColorScaler = 1.0 / m_samplesPerPixel;

    m_viewportU = {m_viewportWidth, 0, 0};
    m_viewportV = {0, -m_viewportHeight, 0};

    m_deltaU = m_viewportU / m_imageWidth;
    m_deltaV = m_viewportV / m_imageHeight;

    m_viewportUpperLeft = m_location - Vector3(0, 0, m_focalLength) - m_viewportU/2 -m_viewportV/2;
    m_pixel00Location = m_viewportUpperLeft + (m_deltaU*0.5 + m_deltaV*0.5);
}

};