/* Start Header ---------------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name : SplashScreen.hpp
Language  : C++
Platform  : Visual Studio 2017
Project   : CamPic
Primary   : JinHyun Choi
Secondary :
- End Header ----------------------------------------------------------------*/
#pragma once
#include "State.hpp"

class SplashScreen : public State
{
public:
	SplashScreen()
	{
		information_ = State_Information::Splash;
	}

	void Initialize() override;
	void Update(float dt) override;
	void ShutDown() override;

private:
	bool ischange_level = false;
	bool ischange = false;
	float time_count = 0.0f;
	Object* logo = nullptr;
	Object* background = nullptr;
};