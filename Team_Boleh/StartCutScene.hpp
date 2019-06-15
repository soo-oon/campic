/* Start Header ---------------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name : StartCutScene.hpp
Language  : C++
Platform  : Visual Studio 2017
Project   : CamPic
Primary   : TaeWook Kang
Secondary :
- End Header ----------------------------------------------------------------*/
#pragma once
#include "State.hpp"
#include "Button.hpp"

class StartCutScene : public State
{
public:
	StartCutScene()
	{
		information_ = State_Information::CutScene;
	}

	void Initialize() override;
	void Update(float dt) override;
	void ShutDown() override;
private:
	Object* start = nullptr;
	Object* start1 = nullptr;
	Object* mouse_icon = nullptr;
	Object* button = nullptr;

	float timer = 0.f;
	bool is_end_start_sprite = false;
	bool is_start_animation = false;
};

