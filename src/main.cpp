#include <iostream>

#include "core/Vector3.h"
#include "core/Color.h"
#include "core/Point3.h"
#include "core/Ray.h"
#include "ecs/Scene.h"
#include "core/CollisionRecord.h"
#include "core/Interval.h"
#include "core/Random.h"
#include "render/Camera.h"

using namespace PathTracer;

int main()
{
    Scene scene;

    //  Scene initialization

    for(int i = 0; i < 5; i++)
    {
        size_t entityId = scene.addEntity();
        scene.addComponent<SphericalRayColliderComponent>(entityId, {randomSphere()});
    }

    //  Writing image to the output in the ppm format

    Camera camera;

    camera.render(scene);

    return 0;
}