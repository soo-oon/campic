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

private:
	std::string current_level = "LevelSelector";

	const std::string file_path = "asset/JsonFiles/Levels/";
};
