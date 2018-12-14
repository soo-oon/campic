/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:  FireBall.hpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

#pragma once
#include "Component.hpp"

class Object;

class FireBall : public Component
{
public:
	FireBall(Object* player_, Object* sword, float time_) : o_player(player_), o_sword(sword), life_time(time_)
	{}

	bool Initialize(Object* Ob) override;
	void Update(float dt) override;
	void Delete() override;

	bool IsDead() { return isdead;  }
private:
	Object* o_player = nullptr;
	Object* o_sword = nullptr;
	float account_time = 0;
	float life_time = 0;
	bool isdead = false;

};
