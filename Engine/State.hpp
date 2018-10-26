#pragma once
#include "Objectmanager.hpp"
#include <vector2.hpp>
#include "WorldPhysics.h"

class State
{
public:
	virtual ~State() {}

    virtual void Load()
    {
		level_change = false;
		objectmanager = new Objectmanager();
		world_physics = new WorldPhysics();
    }
	virtual void Initialize() = 0;
    virtual void Update(float dt) = 0;
	virtual void ShutDown() = 0;
	virtual  void UnLoad()
	{
		change_level.clear();
		delete objectmanager;
		delete world_physics;
	}

	virtual Objectmanager* GetObjectManager() { return objectmanager; }
	virtual WorldPhysics* GetWorldPhyics() { return world_physics; }
	virtual vector2 GetStateScreenSize() { return screen_size_; }
	virtual void SetStateScreenSize(vector2 size) { screen_size_ = size; }
	virtual bool IsLevelChange() { return level_change; }
	virtual std::string GetNextLevel() { return change_level; }

	virtual void ChangeLevel(std::string ID)
	{
		level_change = true;
		change_level = ID;
	}

private:
	std::string change_level;

	bool level_change = false;
	Objectmanager * objectmanager = nullptr;
	WorldPhysics* world_physics = nullptr;
	vector2 screen_size_{};

    //virtual void Unload() = 0;
};
