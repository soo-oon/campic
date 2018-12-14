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
#include "System.hpp"
#include <map>
#include <string>
#include <memory>
#include "Object.hpp"

enum class State_Information
{
	None,
	Splash,
	Menu,
	Game,
	MapEditor,
	size
};

class State;

class StateManager : public System
{
public:
	StateManager() = default;
	~StateManager() = default;

	void AddStage(std::string ID, State* state);
	void ChangeStage();
	void Restart();
	void Pause();
	State* GetCurrentState() { return m_currentState; }
	std::map <std::string, std::unique_ptr<State>>& GetStateMap() { return states; }

	bool Initialize() override;
	void Update(float dt) override;
	void Quit() override;
private:
	State* m_currentState = nullptr;
	std::map <std::string, std::unique_ptr<State>> states;

	bool m_restart, m_pause;
};