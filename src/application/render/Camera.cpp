#include "Camera.h"
#include "Random.h"
#include "RayIntersectionSystem.h"
#include "Timer.h"

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
                pixelColor += RayIntersectionSystem::rayColor(scene, r, m_maxDepth);
            }
            writeColor(pixelColor * m_pixelColorScaler);
        }
    }
    std::clog << "\rDone                    \n" ;
}

void Camera::initialize()
{
    m_imageHeight = static_cast<int>(m_imageWidth/m_aspectRatio);

    m_pixelColorScaler = 1.0 / m_samplesPerPixel;

    auto focalLength = (m_location - m_lookAt).length();

    auto h = std::tan(degreesToRadians(m_fov) / 2);

    auto viewportHeight = 2 * h * focalLength;
    auto viewportWidth = viewportHeight * (static_cast<double>(m_imageWidth)/m_imageHeight);

    m_w = unitVector(m_location - m_lookAt);
    m_u = unitVector(cross(m_viewUp, m_w));
    m_v = cross(m_w, m_u);

    Vector3 viewportU = viewportWidth * m_u;;
    Vector3 viewportV = viewportHeight * -1*m_v;;

    m_deltaU = viewportU / m_imageWidth;
    m_deltaV = viewportV / m_imageHeight;
    auto viewportUpperLeft = m_location - focalLength *m_w - viewportU/2 -viewportV/2;
    m_pixel00Location = viewportUpperLeft + (m_deltaU*0.5 + m_deltaV*0.5);
}

};