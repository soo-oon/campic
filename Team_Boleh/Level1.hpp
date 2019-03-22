#pragma once
#include "State.hpp"

class Level1 : public State
{
public:
	Level1()
	{
		information_ = State_Information::Game;
	}

	void Initialize() override;
	void Update(float dt) override;
	void ShutDown() override;

};
