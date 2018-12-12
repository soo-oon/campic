#pragma once
#include "Objectmanager.hpp"
#include <vector2.hpp>
#include "Sound.hpp"
#include "Player.hpp"

class JSON;

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
	virtual void UnLoad();


	virtual void AddPlayer();

	virtual void SetCamera() { camera = true; }
	virtual bool IsCamera() { return camera; }
	virtual std::unique_ptr<Objectmanager>& GetObjectManager(){return objectmanager;}
	virtual vector2 GetStateScreenSize() { return screen_size_; }
	virtual void SetStateScreenSize(vector2 size) { screen_size_ = size; }
	virtual bool IsLevelChange() { return level_change; }
	virtual std::string GetNextLevel() { return change_level; }
	virtual Sound* GetSoundMap() { return sound; }
	virtual void ChangeLevel(std::string ID);
	virtual JSON* GetJson() { return json; };
	virtual void SetObjectManager(Objectmanager* objectmanager_) { objectmanager = objectmanager_; }

private:
	std::string change_level;

	bool camera = false;
	bool level_change = false;
	std::unique_ptr<Objectmanager> objectmanager;
	//Objectmanager * objectmanager = nullptr;
	Sound* sound = nullptr;
	vector2 screen_size_{};
	
	JSON* json = nullptr;
};
