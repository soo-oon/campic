#pragma once
#include "System.hpp"
#include <map>
#include <string>
#include <memory>
#include "Object.hpp"

enum class State_Information
{
	None,
	Splash,
	Menu,
	Game,
	size
};

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
	std::map <std::string, std::unique_ptr<State>>& GetStateMap() { return states; }

	void check();

    bool Initialize() override;
    void Update(float dt) override;
    void Quit() override;
private:
    State* m_currentState = nullptr;

	Object* player;
	Object* sword;
	//std::unique_ptr<Object> sword;

	std::map <std::string, std::unique_ptr<State>> states;
    bool m_restart, m_pause;
};