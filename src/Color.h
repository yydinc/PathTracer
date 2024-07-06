#ifndef COLOR_H
#define COLOR_H


#include "Vector3.h"

namespace PathTracer
{

using Color = Vector3;

inline void writeColor(const Color &color)
{
    std::cout << static_cast<int>(255.999 * color.r) << ' '
              << static_cast<int>(255.999 * color.g) << ' '
              << static_cast<int>(255.999 * color.b) << '\n';
}

}


#endif  //  COLOR_H