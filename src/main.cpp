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

//    Scene scene = FileParser::parseSceneFile("../src/sample.scene");

    Scene scene;

    for(int i = 0; i < MAX_ENTITIES; i++)
    {
        size_t entityId = scene.addEntity();
        scene.addComponent<TransformComponent>(entityId, {randomVector({-100, 100})});
        scene.addComponent<RayColliderComponent>(entityId, {ColliderType::Spherical, randomDouble({-100, 100})});
    }

    Camera camera = FileParser::parseCameraFile("../src/sample.camera");

    camera.render(scene);

    return 0;
}