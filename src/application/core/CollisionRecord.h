#ifndef HIT_RECORD_H
#define HIT_RECORD_H


#include <memory>

#include "Point3.h"
#include "Vector3.h"
#include "Constants.h"

namespace PathTracer
{

struct CollisionRecord
{
    Point3 point;
    Vector3 outwardNormal;
    double t = infinity;
    bool frontFace;
};

};

#endif  //  HIT_RECORD_H
