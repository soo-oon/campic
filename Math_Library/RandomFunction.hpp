#pragma once
#include <chrono>
#include <random>

template<typename  T>
T RandomNumberGenerator(T min, T max)
{
	int current_time = static_cast<int>(std::chrono::system_clock::now().time_since_epoch().count());

	std::mt19937 rand(current_time);

	std::uniform_real_distribution<T> distribution(min, max);

	return static_cast<T>(distribution(rand));
}
