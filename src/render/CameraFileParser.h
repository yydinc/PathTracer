#ifndef CAMERA_FILE_PARSER_H
#define CAMERA_FILE_PARSER_H


#include <optional>

#include "Camera.h"

namespace PathTracer::FileParser
{

std::optional<Camera> parseCameraFile(const std::string &cameraFileName);

};

#endif  //  CAMERA_FILE_PARSER_H
