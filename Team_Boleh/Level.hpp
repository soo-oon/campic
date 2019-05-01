#pragma once
#include "State.hpp"

class Level : public State
{
public:
	Level()
	{
		information_ = State_Information::Game;
	}
	void Initialize() override;
	void Update(float dt) override;
	void ShutDown() override;
private:
	Object* m_door = nullptr;
    Object* camera = nullptr;
	Object* background = nullptr;

};
