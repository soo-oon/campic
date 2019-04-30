/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: StateManager.hpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include "Object.hpp"

enum class State_Information
{
	None,
	Splash,
	Menu,
	Game,
	HUD,
	MapEditor,
	size
};

class State;

class StateManager
{
public:
	bool Initialize();
	void Update(float dt);
	void Quit();

	void AddStage(std::string ID, State* state);
	void BackToMenu();
	void ChangeStage();
	void Restart();
	void Pause();

	void SetCurrentLevelCaptureLimit();
	void TogglePause() { m_pause = !m_pause; }
	State* GetCurrentState() { return m_currentState; }

	bool IsPause() { return m_pause; }

	std::unordered_map <std::string, std::unique_ptr<State>>& GetStateMap() { return states; }

private:
	State* m_currentState = nullptr;
	std::unordered_map <std::string, std::unique_ptr<State>> states;

	bool m_restart = false, m_pause = false;
};

extern StateManager StateManager_;