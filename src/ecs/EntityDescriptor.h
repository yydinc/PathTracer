#ifndef ENTITY_DESCRIPTOR_H
#define ENTITY_DESCRIPTOR_H


#include "Constants.h"

namespace PathTracer
{

struct EntityDescriptor
{
    size_t id;
    ComponentMask mask;
};

};

#endif  //  ENTITY_DESCRIPTOR_H
