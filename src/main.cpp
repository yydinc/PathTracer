#include <iostream>

#include "ecs/Scene.h"
#include "render/Camera.h"
#include "ecs/SceneFileParser.h"
#include "render/CameraFileParser.h"
#include "core/Random.h"

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
            scene.addComponent<SphericalRayColliderComponent>(entityId,
                                                              {{{randomDouble({-1, 1}), randomDouble({-1, 1}),
                                                                 randomDouble({-1, 1})}, randomDouble({0, 1})}});
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