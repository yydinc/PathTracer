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

    double x = fileRoot->getDouble("X");
    double y = fileRoot->getDouble("Y");
    double z = fileRoot->getDouble("Z");
    double aspectRatio = fileRoot->getDouble("AspectRatio");
    int imageWidth = fileRoot->getInt("ImageWidth");
    double focalLength = fileRoot->getDouble("FocalLength");
    double viewportHeight = fileRoot->getDouble("ViewportHeight");
    int samplesPerPixel = fileRoot->getInt("SamplesPerPixel");
    int maxDepth = fileRoot->getInt("MaxDepth");

    return Camera{{x, y, z}, aspectRatio, imageWidth, focalLength, viewportHeight, samplesPerPixel, maxDepth};
}

};