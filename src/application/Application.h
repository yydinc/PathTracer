#ifndef APPLICATION_H
#define APPLICATION_H


#include "Constants.h"
#include "SceneFileParser.h"
#include "CameraFileParser.h"
#include "Camera.h"

namespace PathTracer
{

class Application
{
 public:
    Application(const std::string &cameraFilePath, const std::string &sceneFilePath)
    {
        Scene scene = FileParser::parseSceneFile(sceneFilePath);
        Camera camera = FileParser::parseCameraFile(cameraFilePath);

        camera.render(scene);
    }
};

void runApplicationWithArgs(int argc, const char** argv)
{
    if(argc != 3)
    {
        std::cerr << "This program requires 2 arguments to run! (example: ./example-executable example.camera example.scene)\n";
        return;
    }

    Application pathTracer{argv[1], argv[2]};
}

};

#endif  //  APPLICATION_H
