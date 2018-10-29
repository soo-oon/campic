#pragma once
#include "System.hpp"
#include <map>
#include <string>
#include <memory>

class State;

class StateManager : public System
{
public:
    StateManager() = default;
    ~StateManager() = default;

    void AddStage(std::string ID, State* state);
    void ChangeStage();
    void Restart();
    void Pause();
    State* GetCurrentState() { return m_currentState; }

    bool Initialize() override;
    void Update(float dt) override;
    void Quit() override;
private:
    State* m_currentState = nullptr;

	std::map <std::string, std::unique_ptr<State>> states;
    //std::vector<State*> states;
    bool m_restart, m_pause;
};
