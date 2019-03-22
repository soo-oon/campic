#pragma once
#include "State.hpp"

class Level3 : public State
{
public:
	Level3()
	{
		information_ = State_Information::Game;
	}

	void Initialize() override;
	void Update(float dt) override;
	void ShutDown() override;

};
