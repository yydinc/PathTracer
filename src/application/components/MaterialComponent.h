#ifndef MATERIAL_COMPONENT_H
#define MATERIAL_COMPONENT_H


#include "Color.h"

namespace PathTracer
{

enum MaterialType{Simple, TrueLambertian, Metal, Dielectrics};

struct MaterialComponent
{
    MaterialType materialType;
    Color albedo;
    union
    {
        struct { double refractionIndex; };
        struct { double fuzz; };
    };
};

};

#endif  //  MATERIAL_COMPONENT_H
