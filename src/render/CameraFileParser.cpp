#include "CameraFileParser.h"
#include "../core/FileParser.h"

namespace PathTracer::FileParser
{

std::optional<Camera> parseCameraFile(const std::string &cameraFileName)
{
    if(!cameraFileName.ends_with(".camera"))
    {
        std::cerr << "Wrong file extension (must be .camera)!";
        return {};
    }

    auto parseResult = parseFile(cameraFileName);

    if(!parseResult)
    {
        return {};
    }

    FileParser::FileNode *fileRoot = parseResult.value();

    double x, y, z, aspectRatio, focalLength, viewportHeight;
    int imageWidth, samplesPerPixel;

    auto cameraXQuery = (*fileRoot)["X"];
    if(!cameraXQuery) return {};
    x = std::stod(cameraXQuery.value()->value);

    auto cameraYQuery = (*fileRoot)["Y"];
    if(!cameraYQuery) return {};
    y = std::stod(cameraYQuery.value()->value);

    auto cameraZQuery = (*fileRoot)["Z"];
    if(!cameraXQuery) return {};
    z = std::stod(cameraZQuery.value()->value);

    auto cameraAspectRatioQuery = (*fileRoot)["AspectRatio"];
    if(!cameraAspectRatioQuery) return {};
    aspectRatio = std::stod(cameraAspectRatioQuery.value()->value);

    auto cameraImageWidthQuery = (*fileRoot)["ImageWidth"];
    if(!cameraImageWidthQuery) return {};
    imageWidth = std::stoi(cameraImageWidthQuery.value()->value);

    auto cameraFocalLengthQuery = (*fileRoot)["FocalLength"];
    if(!cameraFocalLengthQuery) return {};
    focalLength = std::stod(cameraFocalLengthQuery.value()->value);

    auto cameraViewportHeightQuery = (*fileRoot)["ViewportHeight"];
    if(!cameraViewportHeightQuery) return {};
    viewportHeight = std::stod(cameraViewportHeightQuery.value()->value);

    auto cameraSamplesPerPixelQuery = (*fileRoot)["SamplesPerPixel"];
    if(!cameraSamplesPerPixelQuery) return {};
    samplesPerPixel = std::stoi(cameraSamplesPerPixelQuery.value()->value);

    return Camera{{x, y, z}, aspectRatio, imageWidth, focalLength, viewportHeight, samplesPerPixel};
}

};