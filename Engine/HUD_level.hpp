#pragma once
#include "State.hpp"

class HUD_level : public State
{
public:
	void Initialize() override;
	void Update(float dt) override;
	void ShutDown() override;

	void SetObjectManager(Objectmanager* objectmanager_) { objectmanager = objectmanager_; }
private:
	int screen_w = 0;
	int screen_h = 0;
	std::vector<std::string> card_name;
	Objectmanager* objectmanager = nullptr;
};
