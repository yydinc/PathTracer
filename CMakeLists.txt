cmake_minimum_required(VERSION 3.26)
project(PathTracer)

set(CMAKE_CXX_STANDARD 20)

add_compile_definitions(DEBUG)

add_executable(PathTracer
        src/core/Vector3.cpp
        src/core/Vector3.h
        src/core/Color.h
        src/core/Point3.h
        src/core/Ray.h
        src/core/Sphere.cpp
        src/core/Sphere.h
        src/ecs/Scene.h
        src/ecs/components/SphericalRayColliderComponent.h
        src/core/Shape.h
        src/core/CollisionRecord.h
        src/core/Interval.h
        src/core/Random.h
        src/core/Constants.h
        src/ecs/EntityDescriptor.h
        src/ecs/ComponentStorage.h
        src/main.cpp
        src/render/Camera.cpp
        src/render/Camera.h
)
