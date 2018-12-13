#pragma once
#include "State.hpp"

class SplashScreen : public State
{
public:
	SplashScreen()
	{
		information_ = State_Information::Splash;
	}

	void Initialize() override;
	void Update(float dt) override;
	void ShutDown() override;

private:
	float time_count = 0.0f;
	Object* logo = nullptr;
	Object* background = nullptr;
};