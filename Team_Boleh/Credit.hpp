/* Start Header ---------------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name : Credit.hpp
Language  : C++
Platform  : Visual Studio 2017
Project   : CamPic
Primary   : TaeWook Kang
Secondary :
- End Header ----------------------------------------------------------------*/
#pragma once
#include "State.hpp"
#include "MenuPage.hpp"

class Credit : public State
{
public:
	Credit()
	{
		information_ = State_Information::Credit;
	}

	void Initialize() override;
	void Update(float dt) override;
	void ShutDown() override;

private:
	vector2 screen_size = Application_.GetScreenSize();
	Object* m_credit1 = nullptr;
	Object* m_credit2 = nullptr;
	Object* m_credit3 = nullptr;
	Object* m_credit4 = nullptr;
	Object* m_credit5 = nullptr;
	Object* m_credit6 = nullptr;
	Object* mouse_icon = nullptr;
        Object* button = nullptr;

	bool page1 = true;
	bool page2 = false;
	bool page3 = false;
	bool page4 = false;
	bool page5 = false;
	bool page6 = false;

	float timer = 0.f;
};

