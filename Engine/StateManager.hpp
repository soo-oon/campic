#pragma once
#include "System.hpp"
#include <vector>

class State;

class StateManager : public System
{
public:
    StateManager() = default;
    ~StateManager() = default;

    void AddStage(State* state);
    void SetPreviousStage(State* state);
    void SetCurrentStage(State* state);
    void SetPauseStage(State* state);
    void ChangeStage(unsigned stageID);
    void Restart();
    void Pause();
    State* GetCurrentState() { return m_currentStage; }

    bool Initialize() override;
    void Update(float dt) override;
    void Quit() override;
private:
    State *m_pNext = nullptr, *m_pPrevious = nullptr,
          *m_pPaused = nullptr, *m_pRestart = nullptr,
          *m_currentStage = nullptr;

    std::vector<State*> states;
    bool m_restart, m_pause;
};
