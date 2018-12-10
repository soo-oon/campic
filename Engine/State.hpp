#pragma once
#include "Objectmanager.hpp"
#include <vector2.hpp>

class State
{
public:
	virtual ~State()
	{}

	virtual void Load();
	virtual void Initialize() = 0;
	virtual void UpdateObjManager(float dt);
	virtual void Update(float dt) = 0;
	virtual void ShutDown() = 0;
	virtual  void UnLoad();

	virtual void SetCamera() { camera = true; }
	virtual bool IsCamera() { return camera; }
	virtual Objectmanager* GetObjectManager() { return objectmanager; }
	virtual vector2 GetStateScreenSize() { return screen_size_; }
	virtual void SetStateScreenSize(vector2 size) { screen_size_ = size; }
	virtual bool IsLevelChange() { return level_change; }
	virtual std::string GetNextLevel() { return change_level; }

	virtual void ChangeLevel(std::string ID);

private:
	std::string change_level;

	bool camera = false;
	bool level_change = false;
	Objectmanager * objectmanager = nullptr;
	vector2 screen_size_{};
};
