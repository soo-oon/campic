#pragma once
#include "State.hpp"

class MainMenu : public State
{
public:
	MainMenu()
	{
		information_ = State_Information::Menu;
	}

	void Initialize() override;
	void Update(float dt) override;
	void ShutDown() override;

private:
	Object* m_Select = nullptr;
};

