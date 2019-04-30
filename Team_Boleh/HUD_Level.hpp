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

	void CreateHudButton(vector2 pos, vector2 scale /*,std::string & font*/, std::string id);
private:
	Object* h_option_window = nullptr;
	Object* h_cheese = nullptr;
	vector2 screen_size = Application_.GetScreenSize();
};
