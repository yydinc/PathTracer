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
    try
    {
//        Scene scene = FileParser::parseSceneFile("../src/sample.scene");

        Scene scene;

        for(int i = 0; i < MAX_ENTITIES; i++)
        {
            size_t entityId = scene.addEntity();
            scene.addComponent<TransformComponent>(entityId, {randomVector({-1000, 1000})});
            scene.addComponent<RayColliderComponent>(entityId, {ColliderType::Spherical, randomDouble({1, 40})});
        }

        Camera camera = FileParser::parseCameraFile("../src/sample.camera");

        camera.render(scene);
    }
    catch (FileParser::FileParserException &ex)
    {
        std::cerr << "An error occurred while trying to parse files, terminating the program!";
    }

    return 0;
}