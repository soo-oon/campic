/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Timer.hpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

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
