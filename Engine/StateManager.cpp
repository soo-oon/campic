#include "StateManager.hpp"
#include "State.hpp"

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
        m_currentState->Initialize();
    }
}

void StateManager::ChangeStage()
{
	m_currentState = states.find(m_currentState->GetNextLevel())->second.get();
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
        m_currentState->Update(dt);
    }
}

void StateManager::Quit()
{
    states.clear();
}
