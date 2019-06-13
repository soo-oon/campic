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
	bool IsOptionActive() { return IsOptionWindowOpen; }

	Object* CreateHudButton(vector2 pos, vector2 scale, float depth, std::string path, std::string id = "");

	inline static bool IsOptionWindowOpen = false;
	inline static bool ChangeCaptureLimit = false;
private:
	void SetCaptureNumberSprite(Object* one_, Object* double_);
	void SetCapterNumberSprite(Object* base_, Object* sub_);

	//Object* h_chapter = nullptr;
	//OPTION
	Object* h_option_window = nullptr;
	Object* h_fullscreen_button = nullptr;
	Object* h_volume_scroll_button = nullptr;
	Object* h_mute_button = nullptr;
	Object* h_restart_button = nullptr;
	Object* h_backtomenu_button = nullptr;
	Object* h_quit_button = nullptr;
	Object* mouse_icon = nullptr;

	Object* h_capture_limit = nullptr;
	Object* m_capture_one_digits = nullptr;
	Object* m_capture_double_digits = nullptr;

	Object* m_capture_base_num = nullptr;
	Object* m_capture_sub_num = nullptr;
	Object* m_capture_underbar = nullptr;


	Object* h_cheese = nullptr;
	Object* h_select = nullptr;
	vector2 screen_size = Application_.GetScreenSize();
	vector2 scrollbar = vector2(screen_size.x - 1000, screen_size.y - 800);

	bool is_game_state = false;
	bool mute = false;
	bool fullscreen = false;

	
};
