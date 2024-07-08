#ifndef CAMERA_H
#define CAMERA_H


#include "Vector3.h"
#include "Point3.h"
#include "ecs/Scene.h"
#include "Color.h"

namespace PathTracer
{

class Camera
{
 public:
    Camera() = default;
    ~Camera() = default;

    Color rayColor(const Scene &scene, const Ray &ray) const;
    void render(const Scene &scene) const;

 private:
    Point3 m_location{0, 0, 0};

    double m_aspectRatio = 16.0 / 9.0;

    int m_imageWidth = 480;
    int m_imageHeight = static_cast<int>(m_imageWidth/m_aspectRatio);

    double m_focalLength = 1.0;
    double m_viewportHeight = 2.0;
    double m_viewportWidth = m_viewportHeight * (static_cast<double>(m_imageWidth)/m_imageHeight);

    Vector3 m_viewportU{m_viewportWidth, 0, 0};
    Vector3 m_viewportV{0, -m_viewportHeight, 0};

    Vector3 m_deltaU = m_viewportU / m_imageWidth;
    Vector3 m_deltaV = m_viewportV / m_imageHeight;

    Point3 m_viewportUpperLeft = m_location - Vector3(0, 0, m_focalLength) - m_viewportU/2 -m_viewportV/2;
    Point3 m_pixel00Location = m_viewportUpperLeft + (m_deltaU*0.5 + m_deltaV*0.5);

};

};

#endif  //  CAMERA_H
