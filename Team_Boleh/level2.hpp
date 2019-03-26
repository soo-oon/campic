/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:  level2.hpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Jun Soon Woo
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

#pragma once
#include "State.hpp"
#include "Object.hpp"

class level2 : public State
{
public:
	level2()
	{
		information_ = State_Information::Game;
	}

	void Initialize() override;
	void Update(float dt) override;
	void ShutDown() override;

private:
	std::vector<Object*> obj;
	Object* player_camera = nullptr;
};