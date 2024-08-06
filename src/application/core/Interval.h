#ifndef INTERVAL_H
#define INTERVAL_H


#include "Constants.h"

namespace PathTracer
{

class Interval
{
 public:
    Interval(double start, double end) : start(start), end(end) {}
    Interval() : start(-infinity), end(infinity) {}
    ~Interval() = default;

    inline bool contains(double d) const
    {
        return (start <= d) && (d <= end);
    }

    inline bool surrounds(double d) const
    {
        return (start < d) && (d < end);
    }

    inline double clamp(double d) const
    {
        return (d < start) ? start : ((d > end) ? end : d);
    }

    static const Interval empty, universe;

 public:
    double start, end;
};

inline const Interval Interval::empty = Interval{infinity, -infinity};
inline const Interval Interval::universe = Interval{-infinity, infinity};

};

#endif  //  INTERVAL_H
