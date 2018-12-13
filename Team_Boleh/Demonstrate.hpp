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
	void MakeItVisible(int stage_id, bool visible_yes);

};