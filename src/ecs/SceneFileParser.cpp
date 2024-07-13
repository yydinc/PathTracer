#include "SceneFileParser.h"

namespace PathTracer::FileParser
{

static void parseComponent(FileNode *componentRoot, Scene &scene, size_t entityId)
{
    if(componentRoot->name == "SphericalRayColliderComponent")
    {
        double x, y, z, r;

        FileNode *sphereRoot = (*componentRoot)["Sphere"];

        x = sphereRoot->getDouble("X");
        y = sphereRoot->getDouble("Y");
        z = sphereRoot->getDouble("Z");
        r = sphereRoot->getDouble("R");

        scene.addComponent<SphericalRayColliderComponent>(entityId, {{{x, y, z}, r}});
    }
    else
    {
        throw FileParserException();
    }
}

static void parseEntity(FileNode *entityRoot, Scene &scene)
{
    size_t entityId = scene.addEntity();
    if(entityRoot->childrenCount == 0) throw FileParserException();

    for(int i = 0; i < entityRoot->childrenCount; i++)
    {
        FileNode *component = entityRoot->children[i];
        parseComponent(component, scene, entityId);
    }
}

Scene parseSceneFile(const std::string &sceneFileName)
{
    if(!sceneFileName.ends_with(".scene"))
    {
        throw FileParserException();
    }

    FileParser::FileNode *fileRoot = parseFile(sceneFileName);

    FileNode *entitiesRoot = (*fileRoot)["Entities"];

    Scene scene;

    for(int i = 0; i < entitiesRoot->childrenCount; i++)
    {
        parseEntity(entitiesRoot->children[i], scene);
    }

    return scene;
}

};