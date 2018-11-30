#pragma once
#include "State.hpp"

class HUD_level : public State
{
public:
	void Initialize() override;
	void Update(float dt) override;
	void ShutDown() override;
private:
	int screen_w = 0;
	int screen_h = 0;
};
