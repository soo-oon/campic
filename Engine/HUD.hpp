/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: HUD_System.hpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/
#pragma once
#include "State.hpp"
#include "Objectmanager.hpp"

class HUD
{
public:
	bool Initialize();
	void Update(float dt);
	void Quit();

	Objectmanager* Get_HUD_ObjectManager() { return object_manager_HUD; }

private:
	State* hud_level = nullptr;
	Objectmanager* object_manager_HUD = nullptr;
};

extern HUD HUD_;