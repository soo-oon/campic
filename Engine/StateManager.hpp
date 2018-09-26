#pragma once
#include "System.hpp"
#include <vector>

class Stage;

class StateManager : public System
{
public:
    StateManager() = default;
    ~StateManager() = default;

    void AddStage(Stage* stage);
    void SetStartStage(Stage* stage);
    void SetCurrentStage(Stage* stage);
    void SetPauseStage(Stage* stage);
    void ChangeStage(unsigned stageID);
    void Restart();
    void Pause();

    bool Initialize() override;
    void Update(float dt) override;
    void Quit() override;
private:
    Stage *m_pNext = nullptr, *m_pFirst = nullptr,
          *m_pPaused = nullptr, *m_pRestart = nullptr,
          *m_currentStage = nullptr;

    std::vector<Stage*> stages;
    bool m_restart, m_pause;
};

extern StateManager* ex;