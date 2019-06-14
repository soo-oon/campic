#pragma once
#include "State.hpp"



class HowToPlay : public State
{
public:
	HowToPlay()
	{
		information_ = State_Information::HowToPlay;
	}

	void Initialize() override;
	void Update(float dt) override;
	void ShutDown() override;

	
private:
	Object* m_select = nullptr;
	Object* mouse_icon = nullptr;
	Object* button = nullptr;
	
};

