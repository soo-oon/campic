#include "StateManager.hpp"
#include "Stage.hpp"

bool StateManager::Initialize()
{
    m_currentStage = nullptr;
    m_pause = false;
    m_restart = false;
    return true;
}

void StateManager::AddStage(State* state)
{
    states.push_back(state);

    if (m_currentStage == nullptr)
    {
        m_currentStage = states[0];
        m_currentStage->Initialize();
    }
}

void StateManager::SetPreviousStage(State* state)
{
	m_pPrevious = state;
}

void StateManager::SetCurrentStage(State* state)
{
    m_currentStage = state;
}

void StateManager::SetPauseStage(State* state)
{
    m_pPaused = state;
}

void StateManager::ChangeStage(unsigned stageID)
{
	//m_pNext
	//m_pPrevious
    m_currentStage = states[stageID];
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
    if (m_pause == false)
    {
        m_currentStage->Update(dt);
    }
}

void StateManager::Quit()
{
    delete m_pNext;
    delete m_pPrevious;
    delete m_pPaused;
    delete m_pRestart;
    delete m_currentStage;

    states.clear();
}
