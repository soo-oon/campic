#pragma once
#include "State.hpp"

class StartCutScene : public State
{
public:
	StartCutScene()
	{
		information_ = State_Information::CutScene;
	}

	void Initialize() override;
	void Update(float dt) override;
	void ShutDown() override;
private:
	Object* start = nullptr;
	Object* start1 = nullptr;

	float timer = 0.f;
	bool is_end_start_sprite = false;
	bool is_start_animation = false;
};

