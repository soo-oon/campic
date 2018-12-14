/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: HUD_level.hpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/
#pragma once
#include "State.hpp"
#include <memory>

class HUD_level : public State
{
public:
	HUD_level()
	{
		information_ = State_Information::None;
	}

	void Initialize() override;
	void Update(float dt) override;
	void ShutDown() override;

private:
	int screen_w = 0;
	int screen_h = 0;
	std::vector<std::string> card_name;

	bool first_deck_occupied = false;
	bool second_deck_occupied = false;
};
