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
		information_ = State_Information::Menu;
	}

	void Initialize() override;
	void Update(float dt) override;
	void ShutDown() override;

	void CreateLevelButton(vector2 pos, vector2 scale, std::string level_text, /*std::string& font,*/ std::string level_id
	,MenuPage* menu);
	void CreateMenuPage();

private:
	std::string current_level = "LevelSelector";
	const std::string file_path = "asset/JsonFiles/Levels/";

	Object* m_SelectLevel = nullptr;
	Object* mouse_icon = nullptr;
private:
	std::map<std::string, bool> m_LevelLock;
	MenuPage* m_Menu1;
	MenuPage* m_Menu2;

	bool selectPage = true;
};
