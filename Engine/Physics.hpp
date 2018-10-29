#pragma once
#include "System.hpp"
#include "Objectmanager.hpp"

class Physics : public System
{
public:
	bool Initialize() override;
	void Update(float dt) override;
	void PhysicsObjectUpdate(Objectmanager* objectmanager);
	void Quit() override;

private:
	Objectmanager* temp_obj = nullptr;
};
