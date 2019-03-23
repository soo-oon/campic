#pragma once
#include "State.hpp"

class MainMenu : public State
{
public:
	MainMenu()
	{
		information_ = State_Information::Menu;
	}

	void Initialize() override;
	void Update(float dt) override;
	void ShutDown() override;

private:
	std::vector<Object*> container;

	bool click = false;

	Object* player_camera = nullptr;
	Object* start_button = nullptr;
	Object* option_button = nullptr;
	Object* quit_button = nullptr;
};

