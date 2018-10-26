#include "StateManager.hpp"
#include "State.hpp"

bool StateManager::Initialize()
{
    m_currentStage = nullptr;
    m_pause = false;
    m_restart = false;
    return true;
}

void StateManager::AddStage(std::string ID, State* state)
{
	states.insert(std::make_pair(ID, state));

    if (m_currentStage == nullptr)
    {
        m_currentStage = states.find(ID)->second.get();
        m_currentStage->Initialize();
    }
}

void StateManager::ChangeStage()
{
	m_currentStage = states.find(m_currentStage->GetNextLevel())->second.get();
	m_currentStage->Initialize();
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
	if (m_currentStage->IsLevelChange())
		ChangeStage();

    if (m_pause == false)
    {
        m_currentStage->Update(dt);
    }
}

void StateManager::Quit()
{
    delete m_currentStage;

    states.clear();
}
