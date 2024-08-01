#include "Camera.h"
#include "../core/Random.h"
#include "../ecs/systems/RayCollisionDetectionSystem.h"
#include "../core/Timer.h"

namespace PathTracer
{

void Camera::render(const Scene &scene) const
{
    std::cout << "P3\n" << m_imageWidth << ' ' << m_imageHeight << "\n255\n";
    for (int j = 0; j < m_imageHeight; j++) {
        std::clog << "\rScanlines Remaining: " << (m_imageHeight - j) << ' ' << std::flush;
        for (int i = 0; i < m_imageWidth; i++) {
            Color pixelColor{0};
            for (int sample = 0; sample < m_samplesPerPixel; sample++) {
                Point3 pixelLocation = m_pixel00Location + m_deltaU * (i + randomDouble({-0.5, 0.5})) +
                                       m_deltaV * (j + randomDouble({-0.5, 0.5}));
                Vector3 rayDirection = pixelLocation - m_location;

                Ray r(m_location, rayDirection);
                pixelColor += RayCollisionDetectionSystem::rayColor(scene, r);
            }
            writeColor(pixelColor * m_pixelColorScaler);
        }
    }
    std::clog << "\rDone            \n" ;
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