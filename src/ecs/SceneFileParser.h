#ifndef SCENE_FILE_PARSER_H
#define SCENE_FILE_PARSER_H


#include <fstream>
#include <iostream>
#include <string>

#include "Scene.h"
#include "../core/FileParser.h"

namespace PathTracer::FileParser
{

std::optional<Scene> parseSceneFile(const std::string &sceneFileName);

};

#endif  //  SCENE_FILE_PARSER_H
