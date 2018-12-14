/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:  Demonstrate.hpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Jihun Park
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/
#pragma once
#include "State.hpp"

class Demonstrate : public State
{
public:
	Demonstrate()
	{
		information_ = State_Information::Game;
	}
	void Initialize() override;
	void Update(float dt) override;
	void ShutDown() override;

private:
	int selected_level = 0;

	std::map<std::string, Object> stage0;
	std::map<std::string, Object> stage1;

	void CreateLoadObject(int stage_id);
	void DrawStage(int selected_stage_id);
	void DrawStage0();
	void DrawStage1();

	Object player_info;
	Object sword_info;
};