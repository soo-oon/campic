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
#include "Sword.hpp"
#include "Player.hpp"

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
		m_currentState = states.find(ID)->second.get();

		m_currentState->AddPlayer();
		m_currentState->Initialize();
		/*if (states.find(ID)->second->information_ == State_Information::Splash)
		{
			m_currentState = states.find(ID)->second.get();
			m_currentState->Load();
			m_currentState->Initialize();
		}*/
	}
}

void StateManager::ChangeStage()
{
	std::string next_level = m_currentState->GetNextLevel();

	//m_currentState->UnLoad();

	m_currentState = states.find(next_level)->second.get();

	//m_currentState->Load();

	//if (m_currentState->information_ == State_Information::Game)
	//{
	//	m_currentState->AddPlayer();
	//}
	//m_currentState->GetObjectManager()->Initialize();

	m_currentState->Initialize();
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
		//m_currentState->UpdateObjManager(dt);
		m_currentState->Update(dt);
		//m_currentState->UpdateJsonState(this);
	}
}

void StateManager::Quit()
{
	states.clear();
}
