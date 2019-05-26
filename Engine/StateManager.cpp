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
#include <fstream>

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
			m_currentState = first_level.get();
		}
		m_currentState->SetLevelIndicator(ID);
		m_currentState->Initialize();
	}
}

void StateManager::ChangeStage()
{
	std::string next_level = "Level";
	std::string save = m_currentState->GetLevelIndicator();

	m_currentState->ShutDown();
	m_currentState->ResetLevelChange();
	m_currentState = states.find(next_level)->second.get();

	m_currentState->LoadLevel(save);
	m_currentState->SetLevelIndicator(save);
	SetCurrentLevelCaptureLimit();

    m_currentState->CreateCaptureCamera();
    
	if (m_currentState->GetCurrentStateInfo() == State_Information::Game)
	{
		m_currentState->CreatePlayer();
	}

	m_currentState->Initialize();

	Physics_.ResetPreviousSize();
}

void StateManager::BackToMenu()
{	
	m_currentState->ShutDown();
	m_currentState->ResetBackToMenu();
	m_currentState = states.find("LevelSelector")->second.get();

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

void StateManager::SetCurrentLevelCaptureLimit()
{
	std::string file_path = "asset/JsonFiles/Levels/";
	file_path.append(GetCurrentState()->GetLevelIndicator()+"/");
	file_path.append("capture_limit.txt");
	std::string num_limit;

	std::ifstream myfile(file_path.data());

	if(myfile.is_open())
	{
		std::getline(myfile, num_limit);
		GetCurrentState()->SetCaptureLimit(stoi(num_limit));

		myfile.close();
	}
}

void StateManager::Update(float dt)
{
	if (m_currentState->GetCurrentStateInfo() == State_Information::Game)
	{
		if (Input::IsKeyTriggered(GLFW_KEY_ESCAPE))
			TogglePause();
	}

     if (m_currentState->IsLevelChange())
     {
         ChangeStage();
         if (m_currentState->GetPlayerObjectPointer())
             m_currentState->GetPlayerObjectPointer()->GetTransform().SetTranslation(m_currentState->GetStartPosition());
     }

	if (m_currentState->IsBackToMenu())
		BackToMenu();

	m_currentState->Update(dt);

	if(Input::IsKeyTriggered(GLFW_KEY_T))
	{
		m_currentState->GetNextLevel();
	}
}

void StateManager::Quit()
{
	states.clear();
}
