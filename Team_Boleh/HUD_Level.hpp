#pragma once
#include "State.hpp"
#include "Application.hpp"

class HUD_Level : public State
{
public:
	HUD_Level()
	{
		information_ = State_Information::HUD;
	}

	void Initialize() override;
	void Update(float dt) override;
	void ShutDown() override;

private:
	Object* hp = nullptr;
};
