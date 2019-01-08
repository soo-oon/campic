/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: State.hpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

#pragma once
#include "Objectmanager.hpp"
#include <vector2.hpp>
#include "Sound.hpp"
#include "StateManager.hpp"

class JSON;

class State
{
public:
	//virtual void Load();
	//virtual void UnLoad();
	//virtual void UpdateObjManager(float dt);
	//virtual void UpdateJsonState(StateManager* current);
	//virtual std::unique_ptr<Objectmanager>& GetObjectManager(){return objectmanager;}
	//virtual vector2 GetStateScreenSize() { return screen_size_; }
	//virtual void SetStateScreenSize(vector2 size) { screen_size_ = size; }
	//virtual void AddPlayer();
	//virtual void SecondPlanForPlayer(Object* player);
	//virtual JSON* GetJson() { return json; }

	virtual void Initialize() = 0;
	virtual void Update(float dt) = 0;
	virtual void ShutDown() = 0;

	virtual void SetCamera() { iscamera = true; }
	virtual bool IsCamera() { return iscamera; }

	virtual bool IsLevelChange() { return level_change; }
	virtual std::string GetNextLevel() { return change_level; }
	virtual Sound* GetSoundMap() { return sound; }
	virtual void ChangeLevel(std::string ID);
	State_Information information_ = State_Information::None;

private:
	//std::unique_ptr<Objectmanager> objectmanager;
	//vector2 screen_size_{};
	//JSON* json = nullptr;

	std::string change_level;

	bool iscamera = false;
	bool level_change = false;

	Sound* sound = nullptr;
};
