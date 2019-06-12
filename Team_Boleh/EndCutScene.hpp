#pragma once
#include "State.hpp"

class EndCutScene : public State
{
public:
	EndCutScene()
	{
		information_ = State_Information::CutScene;
	}
	void Initialize() override;
	void Update(float dt) override;
	void ShutDown() override;
private:
	Object* end = nullptr;
};

