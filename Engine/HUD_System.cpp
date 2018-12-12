#include "HUD_System.hpp"

bool HUD::Initialize()
{
	hud_level = new HUD_level();
	hud_level->Initialize();
	
	return true;
}

void HUD::Update(float dt)
{
	hud_level->SetObjectManager(object_manager);
	hud_level->Update(dt);
	hud_level->UpdateObjManager(dt);
}

void HUD::Quit()
{

}
