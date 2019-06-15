/* Start Header ---------------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name : LevelSelector.hpp
Language  : C++
Platform  : Visual Studio 2017
Project   : CamPic
Primary   : TaeWook Kang
Secondary :
- End Header ----------------------------------------------------------------*/
#pragma once
#include "State.hpp"
#include "LevelJson.hpp"
#include "ObjectDepth.hpp"
#include "MenuPage.hpp"

class LevelSelector : public State
{
public:
	LevelSelector()
	{
		information_ = State_Information::LevelSelect;
	}

	void Initialize() override;
	void Update(float dt) override;
	void ShutDown() override;

	void CreateLevelButton(vector2 pos, vector2 scale, std::string level_text, std::string level_id	, std::string texture_level, MenuPage* menu);
	void CreateMenu1();
	void CreateMenu2();
	void CreateMenu3();
        void CreateBackButton();

private:
	std::string current_level = "LevelSelector";
	const std::string file_path = "asset/JsonFiles/Levels/";

	Object* m_SelectLevel = nullptr;
	Object* m_selectPage = nullptr;
private:
	std::map<std::string, bool> m_LevelLock;
	MenuPage* m_Menu1 = nullptr;
	MenuPage* m_Menu2 = nullptr;
	MenuPage* m_Menu3 = nullptr;

	Object* cam = nullptr;
	Object* previous = nullptr;
	Object* next = nullptr;
	Object* button = nullptr;
	Object* background = nullptr;
	Object* mouse_icon = nullptr;

	bool selectPage = true;
	int page_count = 1;
};
