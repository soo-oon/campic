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
