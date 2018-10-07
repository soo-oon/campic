#pragma once
#include "test.hpp"
#include "Stage.hpp"
#include "Object.hpp"
#include "Objectmanager.hpp"
#include "WorldPhysics.h"

class example : public State
{
public:
    bool Initialize() override;
    void Update(float dt) override;
    void ShutDown() override;

    Objectmanager object_manager;
	Object temp;
	WorldPhysics* world_physics;
private:
};
