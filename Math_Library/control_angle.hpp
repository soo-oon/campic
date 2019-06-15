/* Start Header ---------------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name : control_angle.hpp
Language  : C++
Platform  : Visual Studio 2017
Project   : CamPic
Primary   : JinHyun Choi
Secondary :
- End Header ----------------------------------------------------------------*/
#pragma once

#include <cmath>
#include <limits>

const float PI = 4.0f * std::atan(1.0f);
const float epsilon = std::numeric_limits<float>::epsilon();


float To_Degree(float a);

float To_Radian(float a);
