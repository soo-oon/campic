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

HUD HUD_;

bool HUD::Initialize()
{
	hud_level = new HUD_level();
	hud_level->Load();
	hud_level->Initialize();

	return true;
}

void HUD::Update(float dt)
{
	if (object_manager_HUD != nullptr)
	{
		if (object_manager_HUD->IsExistPlayer())
		{
			hud_level->obj_hud = object_manager_HUD;
			hud_level->Update(dt);
			hud_level->UpdateObjManager(dt);
		}
	}
}

void HUD::Quit()
{

}
