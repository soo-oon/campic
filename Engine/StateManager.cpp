/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: StateManager.cpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

#include "StateManager.hpp"
#include "State.hpp"
#include "Graphics.hpp"
#include <map>
#include "Player.hpp"
#include "Physics.hpp"

StateManager StateManager_;

bool StateManager::Initialize()
{
	m_currentState = nullptr;

	return true;
}

void StateManager::AddStage(std::string ID, State* state)
{
	states.insert(std::make_pair(ID, state));

	if (m_currentState == nullptr)
	{
		if(auto& first_level = states.find(ID)->second; 
			first_level->information_ == State_Information::Splash)
		{
			m_currentState = first_level.get();
		}
		else
		{
			//TODO Chnage this
			m_currentState = first_level.get();
		}

		m_currentState->Initialize();
	}
}

void StateManager::ChangeStage()
{
	std::string next_level = m_currentState->GetNextLevel();

	m_currentState->ShutDown();
	m_currentState->ResetLevelChange();
	m_currentState = states.find(next_level)->second.get();

	m_currentState->Load();

	m_currentState->Initialize();
	Physics_.ResetPreviousSize();
}

void StateManager::Restart()
{
	m_restart = true;
}

void StateManager::Pause()
{
	m_pause = true;
}

void StateManager::Update(float dt)
{
 	if (m_currentState->IsLevelChange())
		ChangeStage();

	if (m_pause == false)
	{
		m_currentState->Update(dt);
	}
}

void StateManager::Quit()
{
	states.clear();
}
