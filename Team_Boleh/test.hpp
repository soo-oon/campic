#pragma once
#include "State.hpp"

class test : public State
{
public:
	test()
	{
		information_ = State_Information::Game;
	}
	void Initialize() override;
	void Update(float dt) override;
	void ShutDown() override;


private:
};
