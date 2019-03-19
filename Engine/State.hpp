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
#include "AudioManager.hpp"
#include "StateManager.hpp"
#include "JSON.hpp"

class JSON;

class State
{
public:
	virtual void Initialize() = 0;
	virtual void Update(float dt) = 0;
	virtual void ShutDown() = 0;

	virtual void SetCamera() { iscamera = true; }
	virtual bool IsCamera() { return iscamera; }

	virtual bool IsLevelChange() { return level_change; }
	virtual std::string GetNextLevel() { return change_level; }
	virtual void ChangeLevel(std::string ID);

	void ResetLevelChange() { level_change = false; }
	void SetPlayerPointer(Object* obj) { m_player = obj; }

	Object* GetPlayerPointer() { return m_player; }
	void Load();
	void UnLoad();

	State_Information information_ = State_Information::None;

private:
	Object* m_player = nullptr;
	std::string change_level;

	bool iscamera = false;
	bool level_change = false;
};
