#pragma once
#include "State.hpp"

class LevelSelector : public State
{
public:
	LevelSelector()
	{
		information_ = State_Information::Game;
	}

	void Initialize() override;
	void Update(float dt) override;
	void ShutDown() override;

	void CreateLevelButton(vector2 pos, vector2 scale, const char* level_text, /*std::string& font,*/ int numlevel);

private:
	std::string current_level = "LevelSelector";
	const std::string file_path = "asset/JsonFiles/Levels/";

	//const std::string lock_path = 

	Object* m_SelectLevel = nullptr;
private:
	std::vector<Object*> m_Container;
	std::map<int, bool> m_LevelLock;
};
