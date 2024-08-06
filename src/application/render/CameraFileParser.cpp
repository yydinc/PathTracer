#include "CameraFileParser.h"
#include "FileParser.h"

namespace PathTracer::FileParser
{

Camera parseCameraFile(const path &cameraFileName)
{
    if(cameraFileName.extension() != ".camera")
    {
        std::cerr << "Wrong file extension (must be .camera)!";
        return {};
    }

    FileNode *fileRoot = parseFile(cameraFileName);

    Vector3 location, lookAt, viewUp;

    location.x = (*fileRoot)["Location"]->getDouble("X");
    location.y = (*fileRoot)["Location"]->getDouble("Y");
    location.z = (*fileRoot)["Location"]->getDouble("Z");

    viewUp.x = (*fileRoot)["ViewUp"]->getDouble("X");
    viewUp.y = (*fileRoot)["ViewUp"]->getDouble("Y");
    viewUp.z = (*fileRoot)["ViewUp"]->getDouble("Z");

    lookAt.x = (*fileRoot)["LookAt"]->getDouble("X");
    lookAt.y = (*fileRoot)["LookAt"]->getDouble("Y");
    lookAt.z= (*fileRoot)["LookAt"]->getDouble("Z");

    double aspectRatio = fileRoot->getDouble("AspectRatio");
    int imageWidth = fileRoot->getInt("ImageWidth");
    double fov = fileRoot->getDouble("Fov");
    int samplesPerPixel = fileRoot->getInt("SamplesPerPixel");
    int maxDepth = fileRoot->getInt("MaxDepth");

    return Camera{location, lookAt, viewUp, aspectRatio, imageWidth, fov, samplesPerPixel, maxDepth};
}

};