#ifndef CAMERA_H
#define CAMERA_H


#include "Vector3.h"
#include "Point3.h"
#include "Scene.h"
#include "Color.h"

namespace PathTracer
{

class Camera
{
 public:
    Camera() = default;
    Camera(const Point3 &location, const Point3 &lookAt, const Point3 &viewUp, double aspectRatio, int imageWidth, double fov, int samplesPerPixel, int maxDepth) :
    m_location(location),m_lookAt(lookAt), m_viewUp(viewUp), m_aspectRatio(aspectRatio), m_imageWidth(imageWidth), m_fov(fov), m_samplesPerPixel(samplesPerPixel), m_maxDepth(maxDepth)
    {
        initialize();
    }
    ~Camera() = default;

    void initialize();
    void render(const Scene &scene) const;

 private:
    Point3 m_location;
    Point3 m_lookAt;
    Vector3 m_viewUp;

    double m_aspectRatio;

    int m_imageWidth;
    int m_imageHeight;

    double m_fov;

    int m_samplesPerPixel;
    int m_maxDepth;
    double m_pixelColorScaler;

    Vector3 m_u, m_v, m_w;

    Vector3 m_deltaU;
    Vector3 m_deltaV;

    Point3 m_pixel00Location;

};

};

#endif  //  CAMERA_H
