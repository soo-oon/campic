#pragma once

#include <chrono>

class Timer
{
private:
    // Type aliases to make accessing nested type easier
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1>>;

    std::chrono::time_point<clock_t> timestamp;

public:
    Timer() : timestamp(clock_t::now())
    {
    }

    void Reset()
    {
        timestamp = clock_t::now();
    }

    double GetElapsedSeconds() const
    {
        return std::chrono::duration_cast<second_t>(clock_t::now() - timestamp).count();
    }
};
