#include <iostream>

#include "ecs/Scene.h"
#include "render/Camera.h"
#include "ecs/SceneFileParser.h"
#include "render/CameraFileParser.h"

using namespace PathTracer;

int main()
{
    try
    {
        Scene scene = FileParser::parseSceneFile("../src/sample.scene");

        Camera camera = FileParser::parseCameraFile("../src/sample.camera");

        camera.render(scene);
    }
    catch (FileParser::FileParserException)
    {
        std::cerr << "An error occured while trying to parse files, terminating the program!";
    }

    return 0;
}