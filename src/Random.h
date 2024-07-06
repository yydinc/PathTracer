#ifndef RANDOM_H
#define RANDOM_H


#include <limits>

namespace PathTracer
{

static inline uint32_t random(uint32_t input)
{
    uint32_t state = input * 747796405u + 2891336453u;
    uint32_t word = ((state >> ((state >> 28u) + 4u)) ^ state);
    return (word >> 22u) ^ word;
}

static inline double randomDouble(uint32_t input)
{
    uint32_t seed = random(input);
    return (double)seed / (double)std::numeric_limits<uint32_t>::max();
}

};

#endif  //  RANDOM_H
