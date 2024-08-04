cmake_minimum_required(VERSION 3.26)
project(PathTracer)

set(CMAKE_CXX_STANDARD 20)

add_compile_definitions(DEBUG)

include_directories(src/application/core
                    src/application/render
                    src/application/components
                    src/application/systems
                    src/application
                    src/ecs)

add_executable(PathTracer
        src/application/core/Vector3.cpp
        src/application/core/Vector3.h
        src/application/core/Color.h
        src/application/core/Point3.h
        src/application/core/Ray.h
        src/ecs/Scene.h
        src/application/components/RayColliderComponent.h
        src/application/core/CollisionRecord.h
        src/application/core/Interval.h
        src/application/core/Random.h
        src/application/core/Constants.h
        src/ecs/EntityDescriptor.h
        src/ecs/ComponentStorage.h
        src/main.cpp
        src/application/render/Camera.cpp
        src/application/render/Camera.h
        src/application/core/FileParser.h
        src/application/core/SceneFileParser.h
        src/application/render/CameraFileParser.h
        src/application/core/FileParser.cpp
        src/application/core/SceneFileParser.cpp
        src/application/render/CameraFileParser.cpp
        src/application/core/Timer.h
        src/application/components/TransformComponent.h
        "src/application/systems/RayIntersectionSystem.h"
        "src/application/systems/RayIntersectionSystem.cpp"
        src/application/components/MaterialComponent.h
        src/application/Application.h
)
