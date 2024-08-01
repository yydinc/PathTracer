#include <iostream>

#include "core/Random.h"
#include "ecs/Scene.h"
#include "render/Camera.h"
#include "ecs/SceneFileParser.h"
#include "render/CameraFileParser.h"
#include "ecs/components/TransformComponent.h"
#include "ecs/components/RayColliderComponent.h"

using namespace PathTracer;

int main()
{

    Scene scene = FileParser::parseSceneFile("../src/sample.scene");

    Camera camera = FileParser::parseCameraFile("../src/sample.camera");

    camera.render(scene);

    return 0;
}