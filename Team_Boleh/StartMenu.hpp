/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:  StartMenu.hpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : jihun Park
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

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

