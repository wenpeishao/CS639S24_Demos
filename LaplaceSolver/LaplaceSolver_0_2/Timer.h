#pragma once

#include <chrono>
#include <cstring>
#include <iostream>

struct Timer
{
    using clock_t = std::chrono::high_resolution_clock;
    using time_point_t = std::chrono::time_point<clock_t>;

    time_point_t mStartTime;
    time_point_t mStopTime;

    void Start()
    {
        mStartTime = clock_t::now();
    }

    void Stop()
    {
        mStopTime = clock_t::now();
    }

    double Elapsed() const
    {
        return std::chrono::duration<double, std::milli>(mStopTime - mStartTime).count();
    }

    void PrintElapsed(const std::string &msg)
    {
        std::cout << "[" << msg << ": " << Elapsed() << "ms]" << std::endl;
    }
};
