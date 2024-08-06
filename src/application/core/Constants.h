#ifndef CONSTANTS_H
#define CONSTANTS_H


#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <optional>
#include <filesystem>

// Macros

#define ONCE(function) const bool once = [](){function(); return true;}();

namespace PathTracer
{

// Constants

constexpr double infinity = std::numeric_limits<double>::infinity();
constexpr double pi = 3.1415926535897932385;

static constexpr size_t MAX_ENTITIES = 10;
static constexpr size_t MAX_COMPONENTS = 8;
static constexpr size_t MAX_RAY_COLLIDER_TYPE = 2;
static constexpr size_t MAX_MATERIAL_TYPE = 3;

// C++ Std Usings

using std::make_shared;
using std::shared_ptr;

using std::make_unique;
using std::unique_ptr;

using std::weak_ptr;

using std::sqrt;

using std::optional;

using std::filesystem::path;

using ComponentMask = std::bitset<MAX_COMPONENTS>;

// Utility Functions

inline double degrees_to_radians(double degrees)
{
    return degrees * pi / 180.0;
}

};

#endif  //  CONSTANTS_H
