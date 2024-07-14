#ifndef TIMER_H
#define TIMER_H


#include <chrono>

class Timer
{
 public:
    inline void start()
    {
        m_startTimePoint = std::chrono::high_resolution_clock::now();
    }

    inline void stop()
    {
        m_stopTimePoint = std::chrono::high_resolution_clock::now();

        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_startTimePoint).time_since_epoch().count();
        auto stop = std::chrono::time_point_cast<std::chrono::microseconds>(m_stopTimePoint).time_since_epoch().count();

        m_durationMicroSec = stop - start;
    }

    inline long long int durationMicroSec() const { return m_durationMicroSec; }
    inline double durationMiliSec() const { return m_durationMicroSec * 0.001; }


 private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_startTimePoint, m_stopTimePoint;
    long long int m_durationMicroSec;
};


#endif  //  TIMER_H
