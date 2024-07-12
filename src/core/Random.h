#ifndef RANDOM_H
#define RANDOM_H


#include <limits>

#include "Interval.h"

namespace PathTracer
{

static inline uint32_t random()
{
    static uint32_t current_seed = 1233241;
    uint32_t state = current_seed * 747796405u + 2891336453u;
    uint32_t word = ((state >> ((state >> 28u) + 4u)) ^ state);
    return (current_seed = (word >> 22u) ^ word);
}

static inline double randomDouble()
{
    uint32_t seed = random();
    return (double)seed / (double)std::numeric_limits<uint32_t>::max();
}

static inline double randomDouble(const Interval &interval)
{
    return randomDouble() * interval.end - interval.start;
}

static inline double randomDouble(const Interval &&interval)
{
    return randomDouble() * interval.end - interval.start;
}

static inline Sphere randomSphere()
{
    return Sphere{{randomDouble(), randomDouble(), randomDouble()}, randomDouble()};
}

static inline Sphere randomSphere(const Interval &x, const Interval &y, const Interval &z, const Interval &r)
{
    return Sphere{{randomDouble(x), randomDouble(y), randomDouble(z)}, randomDouble(r)};
}

static inline Sphere randomSphere(const Interval &&x, const Interval &&y, const Interval &&z, const Interval &&r)
{
    return Sphere{{randomDouble(x), randomDouble(y), randomDouble(z)}, randomDouble(r)};
}

static inline Sphere randomSphere(const Interval &xyz, const Interval &r)
{
    return Sphere{{randomDouble(xyz), randomDouble(xyz), randomDouble(xyz)}, randomDouble(r)};
}

static inline Sphere randomSphere(const Interval &&xyz, const Interval &&r)
{
    return Sphere{{randomDouble(xyz), randomDouble(xyz), randomDouble(xyz)}, randomDouble(r)};
}

static inline Sphere randomSphere(const Interval &xyzr)
{
    return Sphere{{randomDouble(xyzr), randomDouble(xyzr), randomDouble(xyzr)}, randomDouble(xyzr)};
}

static inline Sphere randomSphere(const Interval &&xyzr)
{
    return Sphere{{randomDouble(xyzr), randomDouble(xyzr), randomDouble(xyzr)}, randomDouble(xyzr)};
}

};

#endif  //  RANDOM_H
