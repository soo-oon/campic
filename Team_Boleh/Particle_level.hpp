#pragma once
#include "State.hpp"

class Particle_level : public State
{
public:
	Particle_level ()
	{
		information_ = State_Information::Game;
	}

	void Initialize() override;
	void Update(float dt) override;
	void ShutDown() override;

private:
};