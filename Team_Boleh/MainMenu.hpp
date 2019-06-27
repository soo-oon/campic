/* Start Header ---------------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name : MainMenu.hpp
Language  : C++
Platform  : Visual Studio 2017
Project   : CamPic
Primary   : TaeWook Kang
Secondary :
- End Header ----------------------------------------------------------------*/
#pragma once
#include "State.hpp"
#include "ObjectDepth.hpp"

class MainMenu : public State
{
public:
	MainMenu()
	{
		information_ = State_Information::Menu;
	}

        void Quitstate();
	void Initialize() override;
	void Update(float dt) override;
	void ShutDown() override;

private:

	Object* m_Select = nullptr;
	Object* are_you_sure = nullptr;
	Object* m_yes = nullptr;
	Object* m_no = nullptr;
        bool callQuit = false;
};

