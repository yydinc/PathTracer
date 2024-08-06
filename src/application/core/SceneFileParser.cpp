#include "SceneFileParser.h"
#include "TransformComponent.h"
#include "MaterialComponent.h"
#include "Color.h"

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
    else if(componentRoot->name == "MaterialComponent")
    {
        MaterialType mt;
        if((*componentRoot)["MaterialType"]->value == "Simple")
        {
            mt = MaterialType::Simple;
        }
        else if((*componentRoot)["MaterialType"]->value == "TrueLambertian")
        {
            mt = MaterialType::TrueLambertian;
        }
        else if((*componentRoot)["MaterialType"]->value == "Metal")
        {
            mt = MaterialType::Metal;
        }
        else if((*componentRoot)["MaterialType"]->value == "Dielectrics")
        {
            mt = MaterialType::Dielectrics;
        }
        else
        {
            throw FileParserException();
        }

        Color albedo;

        albedo.r = (*componentRoot)["Albedo"]->getDouble("R");
        albedo.g = (*componentRoot)["Albedo"]->getDouble("G");
        albedo.b = (*componentRoot)["Albedo"]->getDouble("B");

        if(mt == MaterialType::Metal)
        {
            double fuzz = componentRoot->getDouble("Fuzz");
            scene.addComponent<MaterialComponent>(entityId, {mt, albedo, fuzz});
        }
        else if(mt == MaterialType::Dielectrics)
        {
            double refractionIndex = componentRoot->getDouble("RefractionIndex");
            scene.addComponent<MaterialComponent>(entityId, {mt, albedo, refractionIndex});
        }
        else
        {
            scene.addComponent<MaterialComponent>(entityId, {mt, albedo, 0});
        }
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