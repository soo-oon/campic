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
	State()
	{
		objectmanager = new Objectmanager();
		world_physics = new WorldPhysics();
	}
    virtual ~State()
    {
    };
    //virtual void Load() = 0;
    virtual bool Initialize() = 0;
    virtual void Update(float dt) = 0;
    virtual void ShutDown() = 0;
	virtual Objectmanager* GetObjectManager() { return objectmanager; }
	virtual WorldPhysics* GetWorldPhyics() { return world_physics; }


private:
	Objectmanager * objectmanager;
	WorldPhysics* world_physics;

    //virtual void Unload() = 0;
};
