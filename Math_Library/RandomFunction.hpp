/* Start Header ---------------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name : RandomFunction.hpp
Language  : C++
Platform  : Visual Studio 2017
Project   : CamPic
Primary   : JinHyun Choi
Secondary :
- End Header ----------------------------------------------------------------*/
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
