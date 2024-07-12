cmake_minimum_required(VERSION 3.26)
project(ray_tracing_in_one_weekend)

set(CMAKE_CXX_STANDARD 20)

add_compile_definitions(DEBUG)

add_executable(ray_tracing_in_one_weekend
        PathTracer.h
        src/Vector3.cpp
        src/Vector3.h
        src/Color.h
        src/Point3.h
        src/Ray.h
        src/Sphere.cpp
        src/Sphere.h
        src/ecs/Scene.h
        src/ecs/components/SphericalRayColliderComponent.h
        src/Shape.h
        src/CollisionRecord.h
        src/Interval.h
        src/Random.h
        src/Constants.h
        src/ecs/EntityDescriptor.h
        src/ecs/ComponentStorage.h
        src/main.cpp
        src/Camera.cpp
        src/Camera.h
)
