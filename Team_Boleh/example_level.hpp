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
    std::vector<vector2> opponent;
    std::vector<vector2> mesh_p; 
};

vector2 multi_plus(Object *ob, size_t i);