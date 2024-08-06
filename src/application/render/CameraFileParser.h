#ifndef CAMERA_FILE_PARSER_H
#define CAMERA_FILE_PARSER_H


#include <optional>

#include "Constants.h"
#include "Camera.h"

namespace PathTracer::FileParser
{

Camera parseCameraFile(const path &cameraFileName);

};

#endif  //  CAMERA_FILE_PARSER_H
