#ifndef MATERIAL_COMPONENT_H
#define MATERIAL_COMPONENT_H


namespace PathTracer
{

enum ReflectionType {Simple, TrueLambertian};

struct MaterialComponent
{

    ReflectionType reflectionType;
};

};

#endif  //  MATERIAL_COMPONENT_H
