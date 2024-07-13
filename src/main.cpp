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
#include "core/FileParser.h"
#include "ecs/SceneFileParser.h"
#include "render/CameraFileParser.h"

using namespace PathTracer;

int main()
{
    auto parsedScene = FileParser::parseSceneFile("../src/test.scene");

    if(!parsedScene)
    {
        std::cerr << "Cannot generate scene from scene file!\n";
        return 0;
    }

    Scene scene = std::move(parsedScene.value());

    auto parsedCamera = FileParser::parseCameraFile("../src/test.camera");

    if(!parsedCamera)
    {
        std::cerr << "Cannot generate camera from camera file!\n";
        return 0;
    }

    Camera camera = parsedCamera.value();

    camera.render(scene);

    return 0;
}