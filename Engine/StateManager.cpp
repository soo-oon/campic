#include "StateManager.hpp"
#include "Stage.hpp"

void StateManager::AddStage(Stage * stage)
{
    stages.push_back(stage);
}

void StateManager::SetStartStage(Stage * stage)
{
    m_pFirst = stage;
}

void StateManager::SetCurrentStage(Stage* stage)
{
    m_currentStage = stage;
}

void StateManager::SetPauseStage(Stage * stage)
{
    m_pPaused = stage;
}

void StateManager::ChangeStage(unsigned stageID)
{
    m_currentStage = stages[stageID];
}

void StateManager::Restart()
{
    m_restart = true;
}

void StateManager::Pause()
{
    m_pause = true;
}


bool StateManager::Initialize()
{
    m_currentStage = nullptr;
    m_pause = false;
    m_restart = false;
    return true;
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
    delete m_pFirst;
    delete m_pPaused;
    delete m_pRestart;
    delete m_currentStage;

    stages.clear();
}
