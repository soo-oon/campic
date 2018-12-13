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