#include "SceneFileParser.h"
#include "TransformComponent.h"

namespace PathTracer::FileParser
{

static void parseComponent(FileNode *componentRoot, Scene &scene, size_t entityId)
{
    if(componentRoot->name == "RayColliderComponent")
    {
        double r;
        ColliderType c;

        r = componentRoot->getDouble("R");

        if((*componentRoot)["Type"]->value == "Spherical")
        {
            c = ColliderType::Spherical;
        }
        else
        {
            throw FileParserException();
        }

        scene.addComponent<RayColliderComponent>(entityId, {c, r});
    }
    else if(componentRoot->name == "TransformComponent")
    {
        double x, y, z;

        x = componentRoot->getDouble("X");
        y = componentRoot->getDouble("Y");
        z = componentRoot->getDouble("Z");

        scene.addComponent<TransformComponent>(entityId, {{x, y, z}});
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

Scene parseSceneFile(const path &sceneFileName)
{
    if(sceneFileName.extension() != ".scene")
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