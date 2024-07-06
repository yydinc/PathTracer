#ifndef INTERVAL_H
#define INTERVAL_H


#include "Constants.h"

namespace PathTracer
{

class Interval
{
 public:
    Interval(double start, double end) : m_start(start), m_end(end) {}
    Interval() : m_start(-infinity), m_end(infinity) {}
    ~Interval() = default;

    inline bool contains(double d) const
    {
        return (m_start <= d) && (d <= m_end);
    }

    inline bool surrounds(double d) const
    {
        return (m_start < d) && (d < m_end);
    }

    static const Interval empty, universe;

 private:
    double m_start, m_end;
};

inline const Interval Interval::empty = Interval{infinity, -infinity};
inline const Interval Interval::universe = Interval{-infinity, infinity};

};

#endif  //  INTERVAL_H
