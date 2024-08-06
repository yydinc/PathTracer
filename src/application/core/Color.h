#ifndef COLOR_H
#define COLOR_H


#include "Vector3.h"
#include "Interval.h"

namespace PathTracer
{

using Color = Vector3;

inline double linear_to_gamma(double linear_component)
{
    return std::sqrt(linear_component);
}


inline void writeColor(const Color &color)
{
    Interval i{0, 0.999};

    auto r = linear_to_gamma(color.r);
    auto g = linear_to_gamma(color.g);
    auto b = linear_to_gamma(color.b);

    r = i.clamp(r);
    g = i.clamp(g);
    b = i.clamp(b);

    std::cout << static_cast<int>(255.999 * r) << ' '
              << static_cast<int>(255.999 * g) << ' '
              << static_cast<int>(255.999 * b) << '\n';
}

}


#endif  //  COLOR_H