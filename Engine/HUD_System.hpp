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
#include "System.hpp"
#include "HUD_level.hpp"
#include <memory>
#include "Objectmanager.hpp"

class HUD : public System
{
public:
	bool Initialize() override;
	void Update(float dt) override;
	void Quit() override;

	State* GetHUDlevel() { return hud_level; }
	void SetObjectManager(Objectmanager* objectmanager) { object_manager_HUD = objectmanager; }

private:
	State* hud_level = nullptr;
	Objectmanager* object_manager_HUD = nullptr;
};
