#pragma once
#include "State.hpp"
#include "System.hpp"
#include "HUD_level.hpp"

class HUD : public System
{
public:
	bool Initialize() override;
	void Update(float dt) override;
	void Quit() override;

	State* GetHUDlevel() { return hud_level; }

private:
	State* hud_level = nullptr;
};
