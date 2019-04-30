#pragma once

#include "State.hpp"

class HUD_Level : public State
{
public:
	HUD_Level()
	{
		information_ = State_Information::HUD;
	}

	void Initialize() override;
	void Update(float dt) override;
	void ShutDown() override;

	void CreateHudButton(vector2 pos, vector2 scale, std::string id);
private:
	Object* h_option_window = nullptr;
	Object* h_fullscreen_button = nullptr;
	Object* h_capture_limit = nullptr;
	Object* h_capture_number = nullptr;

	Object* h_cheese = nullptr;
	Object* h_select = nullptr;
	vector2 screen_size = Application_.GetScreenSize();

	bool IsOptionWindowOpen = false;
};
