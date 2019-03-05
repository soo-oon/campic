/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: BossSkill.hpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : HyunSung Kim
Secondary :
Creation date: 2019/03/06
- End Header ----------------------------------------------------------------
*/
#pragma once
#include "Component.hpp"

class Object;

class BossSkill : public Component
{
public:
	BossSkill(Object* boss_, float time_) : o_boss(boss_), life_time(time_)
	{}
	bool Initialize(Object* obj) override;
	void Update(float dt) override;
	void Delete() override;
	Object* GetBossPointer();
	float GetAccountTime();
	float SetAccountTime(float set_account);
	float GetLifeTime();
	float SetLifeTime(float set_life);
	bool IsDead() { return isdead; }

private:
	Object* o_boss;
	float account_time;
	float life_time;
	bool isdead = false;
};