#pragma once
#include "State.hpp"


class Particle_level : public State
{
public:
	void Initialize() override;
	void Update(float dt) override;
	void ShutDown() override;

private:
};