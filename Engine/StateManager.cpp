#include "StateManager.hpp"
#include "State.hpp"
#include "Graphics.hpp"
#include <map>

bool StateManager::Initialize()
{
    m_currentState = nullptr;
    m_pause = false;
    m_restart = false;
    return true;
}

void StateManager::AddStage(std::string ID, State* state)
{
	states.insert(std::make_pair(ID, state));

    if (m_currentState == nullptr)
    {
        m_currentState = states.find(ID)->second.get();
		m_currentState->Load();
		m_currentState->AddPlayer();
        m_currentState->Initialize();
    }
}

void StateManager::ChangeStage()
{
	Object player = *(m_currentState->GetObjectManager()->FindObject("Player").get());
	player.SetTranslation({ -player.GetTransform().GetTranslation().x, player.GetTransform().GetTranslation().y });

	Object sword = *(m_currentState->GetObjectManager()->FindObject("Sword").get());
	sword.SetTranslation({ player.GetTransform().GetTranslation() });

	std::string next_level = m_currentState->GetNextLevel();

	m_currentState->UnLoad();

	m_currentState = states.find(next_level)->second.get();

	m_currentState->Load();

	m_currentState->GetObjectManager()->GetObjectMap().insert(std::make_pair("Player", std::make_unique<Object>(player)));
	m_currentState->GetObjectManager()->GetObjectMap().insert(std::make_pair("Sword", std::make_unique<Object>(sword)));

	m_currentState->GetObjectManager()->Initialize();

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
		m_currentState->UpdateObjManager(dt);
        m_currentState->Update(dt);
    }
}

void StateManager::Quit()
{
    states.clear();
}
