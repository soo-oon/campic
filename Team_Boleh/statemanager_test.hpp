#pragma once
#include "State.hpp"

class test_statemanager : public State
{
public:
	void Initialize() override;
	void Update(float dt) override;
	void ShutDown() override;

private:
	bool check1 = true;
	bool check2 = true;
};