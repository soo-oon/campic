/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: HUD_System.cpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/
#include "HUD.hpp"
#include "Graphics.hpp"
#include <iostream>

HUD HUD_;

bool HUD::Initialize(State* HUD_State)
{
	m_HUD_State = HUD_State;

	if (m_HUD_State != nullptr)
	{
		HUD_Activing_Search();
		hud_camera = new Camera();
		m_HUD_State->Initialize();
	}

	return true;
}

void HUD::Update(float dt)
{
	if(!isHUDActive)
	{
		HUD_Activing_Search();
	}
	if(m_HUD_State != nullptr)
	{
		for(auto obj = HUD_Object_Manager.begin(); obj != HUD_Object_Manager.end(); ++obj)
		{
			for (auto components : obj->get()->GetComponent())
			{
				components->Update(dt);
			}
		}
		m_HUD_State->Update(dt);

	}
}

void HUD::Quit()
{
	HUD_Object_Manager.clear();
	m_HUD_State->ShutDown();

	//delete m_HUD_State;
	//delete m_current_game_state;
	//delete hud_camera;
}

void HUD::Add_HUD_Object(Object* obj)
{
    std::shared_ptr<Object> temp(obj);

    HUD_Object_Manager.push_back(temp);

    for (auto component : HUD_Object_Manager[HUD_Object_Manager.size() - 1]->GetComponent())
    {
        component->Initialize(HUD_Object_Manager[HUD_Object_Manager.size() - 1].get());
    }

    std::stable_sort(HUD_Object_Manager.begin(), HUD_Object_Manager.end(),
        [](auto& obj1, auto& obj2) { return obj1->GetTransform().GetDepth() > obj2->GetTransform().GetDepth(); });
}

void HUD::SetPlayer(Object* obj)
{
}

void HUD::HUD_Activing_Search()
{
	if (auto current_state = StateManager_.GetCurrentState();
		current_state != nullptr)
	{
		if (current_state->GetCurrentStateInfo() == State_Information::Game)
		{
			isHUDActive = true;
			m_current_game_state = current_state;
		}
	}

	isHUDActive = false;
}
