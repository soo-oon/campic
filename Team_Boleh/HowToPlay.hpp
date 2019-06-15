/* Start Header ---------------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name : HowToPlay.hpp
Language  : C++
Platform  : Visual Studio 2017
Project   : CamPic
Primary   : TaeWook Kang
Secondary :
- End Header ----------------------------------------------------------------*/
#pragma once
#include "State.hpp"



class HowToPlay : public State
{
public:
	HowToPlay()
	{
		information_ = State_Information::HowToPlay;
	}

	void Initialize() override;
	void Update(float dt) override;
	void ShutDown() override;

	
private:
	Object* m_select = nullptr;
	Object* mouse_icon = nullptr;
	Object* button = nullptr;
	
};

