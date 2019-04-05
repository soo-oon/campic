#pragma once
#include "State.hpp"

class Test_Level : public State
{
public:
	Test_Level()
	{
		information_ = State_Information::Game;
	}
	void Initialize() override;
	void Update(float dt) override;
	void ShutDown() override;
private:
	std::vector<Object*> obj;
};
