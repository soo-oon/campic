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

	Object* CreateHudButton(vector2 pos, vector2 scale, float depth, std::string path, std::string id = "");
private:
	//OPTION
	Object* h_option_window = nullptr;
	Object* h_fullscreen_button = nullptr;
	Object* h_bgm_scroll_bar = nullptr;
	Object* h_sfx_scroll_bar = nullptr;
	Object* h_bgm_scroll_button = nullptr;
	Object* h_sfx_scroll_button = nullptr;
	Object* h_mute_button = nullptr;
	Object* h_restart_button = nullptr;
	Object* h_quit_button = nullptr;

	Object* h_capture_limit = nullptr;
	Object* h_capture_number = nullptr;

	Object* h_cheese = nullptr;
	Object* h_select = nullptr;
	vector2 screen_size = Application_.GetScreenSize();
	vector2 scrollbar = vector2(screen_size.x - 1000, screen_size.y - 800);

	std::vector<Object*> container;

	bool IsOptionWindowOpen = false;
};
