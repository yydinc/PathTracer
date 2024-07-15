#ifndef RANDOM_H
#define RANDOM_H


#include <limits>

#include "Interval.h"
#include "Vector3.h"

namespace PathTracer
{

inline uint32_t random()
{
    static uint32_t current_seed = 1233241;
    uint32_t state = current_seed * 747796405u + 2891336453u;
    uint32_t word = ((state >> ((state >> 28u) + 4u)) ^ state);
    return (current_seed = (word >> 22u) ^ word);
}

inline double randomDouble()
{
    uint32_t seed = random();
    return (double)seed / (double)std::numeric_limits<uint32_t>::max();
}

inline double randomDouble(const Interval &interval)
{
    return randomDouble() * interval.end - interval.start;
}

inline double randomDouble(const Interval &&interval)
{
    return randomDouble() * interval.end - interval.start;
}

inline Vector3 randomVector()
{
    return {randomDouble(), randomDouble(), randomDouble()};
}

inline Vector3 randomVector(const Interval &interval)
{
    return {randomDouble(interval), randomDouble(interval), randomDouble(interval)};
}

inline Vector3 randomVector(const Interval &&interval)
{
    return {randomDouble(interval), randomDouble(interval), randomDouble(interval)};
}

inline Vector3 randomVector(const Interval &x, const Interval &y, const Interval &z)
{
    return {randomDouble(x), randomDouble(y), randomDouble(z)};
}

inline Vector3 randomVector(const Interval &&x, const Interval &&y, const Interval &&z)
{
    return {randomDouble(x), randomDouble(y), randomDouble(z)};
}

};

#endif  //  RANDOM_H
