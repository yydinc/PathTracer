#ifndef SCENE_FILE_PARSER_H
#define SCENE_FILE_PARSER_H


#include <fstream>
#include <iostream>
#include <string>

#include "Constants.h"
#include "Scene.h"
#include "FileParser.h"

namespace PathTracer::FileParser
{

Scene parseSceneFile(const path &sceneFileName);

};

#endif  //  SCENE_FILE_PARSER_H
