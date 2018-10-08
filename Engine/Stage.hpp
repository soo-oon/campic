#pragma once
#include "Objectmanager.hpp"
#include <vector2.hpp>
#include "WorldPhysics.h"

enum StageList
{
	splash,

};

class State
{
public:
    virtual ~State() {};
    //virtual void Load() = 0;
    virtual bool Initialize() = 0;
    virtual void Update(float dt) = 0;
    virtual void ShutDown() = 0;
    Objectmanager* objectmanager;
    WorldPhysics* world_physics;

    //virtual void Unload() = 0;
};