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
	hud_level->obj_hud = object_manager_HUD;
	hud_level->Update(dt);
	hud_level->UpdateObjManager(dt);
}

void HUD::Quit()
{

}
