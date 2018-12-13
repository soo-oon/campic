#include "HUD_System.hpp"

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
