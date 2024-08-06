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
    Camera(const Point3 &location, double aspectRatio, int imageWidth, double focalLength, double viewportHeight, int samplesPerPixel, int maxDepth) :
    m_location(location), m_aspectRatio(aspectRatio), m_imageWidth(imageWidth), m_focalLength(focalLength), m_viewportHeight(viewportHeight), m_samplesPerPixel(samplesPerPixel), m_maxDepth(maxDepth)
    {
        initialize();
    }
    ~Camera() = default;

    void initialize();
    void render(const Scene &scene) const;

 private:
    Point3 m_location;

    double m_aspectRatio;

    int m_imageWidth;
    int m_imageHeight;

    double m_focalLength;
    double m_viewportHeight;
    double m_viewportWidth;

    int m_samplesPerPixel;
    int m_maxDepth;
    double m_pixelColorScaler;

    Vector3 m_viewportU;
    Vector3 m_viewportV;

    Vector3 m_deltaU;
    Vector3 m_deltaV;

    Point3 m_viewportUpperLeft;
    Point3 m_pixel00Location;

};

};

#endif  //  CAMERA_H