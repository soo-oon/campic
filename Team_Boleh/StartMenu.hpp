#pragma once
#include "State.hpp"

class StartMenu : public State
{
public:
	StartMenu()
	{
		information_ = State_Information::Menu;
	}

	void Initialize() override;
	void Update(float dt) override;
	void ShutDown() override;


	void SetUpButtons(std::string obj_name, vector2 size,
		vector2 position, std::string texture_path);
	void ChangeSelectedMenu();
	void ChangeTexture(int type);
private:
	int select_button_id = 0;
	Object* Start = nullptr;
	Object* Option = nullptr;
	Object* Quit = nullptr;
	bool StartOn = true;
	bool OptionOn = false;
	bool QuitOn = false;
};

