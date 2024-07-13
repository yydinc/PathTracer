#include "SceneFileParser.h"

namespace PathTracer::FileParser
{

static bool parseComponent(FileNode *componentRoot, Scene &scene, size_t entityId)
{
    bool isSuccessful = false;

    if(componentRoot->name == "SphericalRayColliderComponent")
    {
        double x, y, z, r;

        auto sphereQuery = (*componentRoot)["Sphere"];
        if(!sphereQuery.has_value()) return false;
        FileNode *sphereRoot = sphereQuery.value();

        auto sphereXQuery = (*sphereRoot)["X"];
        if(!sphereXQuery.has_value()) return false;
        x = std::stod(sphereXQuery.value()->value);

        auto sphereYQuery = (*sphereRoot)["Y"];
        if(!sphereYQuery.has_value()) return false;
        y = std::stod(sphereYQuery.value()->value);

        auto sphereZQuery = (*sphereRoot)["Z"];
        if(!sphereZQuery.has_value()) return false;
        z = std::stod(sphereZQuery.value()->value);

        auto sphereRQuery = (*sphereRoot)["R"];
        if(!sphereRQuery.has_value()) return false;
        r = std::stod(sphereRQuery.value()->value);

        scene.addComponent<SphericalRayColliderComponent>(entityId, {{{x, y, z}, r}});
        isSuccessful = true;
    }

    return isSuccessful;
}

static bool parseEntity(FileNode *entityRoot, Scene &scene)
{
    size_t entityId = scene.addEntity();
    if(entityRoot->childrenCount == 0) return false;

    for(int i = 0; i < entityRoot->childrenCount; i++)
    {
        FileNode *component = entityRoot->children[i];
        if(!parseComponent(component, scene, entityId)) return false;
    }
    return true;
}

std::optional<Scene> parseSceneFile(const std::string &sceneFileName)
{
    if(!sceneFileName.ends_with(".scene"))
    {
        std::cerr << "Wrong file extension (must be .scene)!";
        return {};
    }

    auto parseResult = parseFile(sceneFileName);

    if(!parseResult)
    {
        return {};
    }

    FileParser::FileNode *fileRoot = parseResult.value();

    auto entitiesQuery = (*fileRoot)["Entities"];
    if(!entitiesQuery) return {};
    FileNode *entitiesRoot = entitiesQuery.value();

    Scene scene;

    for(int i = 0; i < entitiesRoot->childrenCount; i++)
    {
        if(!parseEntity(entitiesRoot->children[i], scene)) return {};
    }

    return scene;
}

};