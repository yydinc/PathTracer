#include <iostream>

#include "Vector3.h"
#include "Color.h"
#include "Point3.h"
#include "Ray.h"
#include "ecs/Scene.h"
#include "CollisionRecord.h"
#include "Interval.h"
#include "Random.h"

using namespace PathTracer;

Color rayColor(Scene &scene, const Ray &ray)
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

Sphere randomSphere()
{
    static uint32_t seed = 1234567;

    double x = randomDouble(seed) * 2 - 1;
    seed = random(seed);

    double y = randomDouble(seed) * 2 - 1;
    seed = random(seed);

    double z = -1;
    seed = random(seed);

    double r = randomDouble(seed) * 0.2;
    seed = random(seed);

    return Sphere{{x, y, z}, r};
}

int main()
{
    double aspectRatio = 16.0 / 9.0;

    int imageWidth = 480;
    int imageHeight = static_cast<int>(imageWidth/aspectRatio);

    double focalLength = 1.0;
    double viewportHeight = 2.0;
    double viewportWidth = viewportHeight * (static_cast<double>(imageWidth)/imageHeight);
    Point3 cameraLocation(0, 0, 0);

    Vector3 viewportU(viewportWidth, 0, 0);
    Vector3 viewportV(0, -viewportHeight, 0);

    Vector3 deltaU = viewportU / imageWidth;
    Vector3 deltaV = viewportV / imageHeight;

    Point3 viewportUpperLeft = cameraLocation - Vector3(0, 0, focalLength) - viewportU/2 -viewportV/2;
    Point3 pixel00Location = viewportUpperLeft + (deltaU*0.5 + deltaV*0.5);

    Scene scene;

    //  Scene initialization

    for(int i = 0; i < 5; i++)
    {
        size_t entityId = scene.addEntity();
        scene.addComponent<SphericalRayColliderComponent>(entityId, {randomSphere()});
    }

    //  Writing image to the output in the ppm format

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j = 0; j < imageHeight; j++) {
        std::clog << "\rScanlines Remaining: " << (imageHeight - j) << ' ' << std::flush;
        for (int i = 0; i < imageWidth; i++) {
            Point3 pixelLocation = pixel00Location + deltaU*i + deltaV*j;
            Vector3 rayDirection = pixelLocation - cameraLocation;

            Ray r(cameraLocation, rayDirection);

            Color pixelColor = rayColor(scene, r);

            writeColor(pixelColor);
        }
    }
    std::clog << "\rDone.               \n";
    return 0;
}