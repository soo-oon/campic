#pragma once
#include "test.hpp"
#include "Stage.hpp"
#include "Object.hpp"
#include "Objectmanager.hpp"
#include "WorldPhysics.h"

class example : public State
{
public:
    example()
    {
        objectmanager = new Objectmanager();
    }
    bool Initialize() override;
    void Update(float dt) override;
    void ShutDown() override;

    //Objectmanager* GetObjectManager() override { return objectmanager_; }
    
	//WorldPhysics* world_physics;
private:
};
