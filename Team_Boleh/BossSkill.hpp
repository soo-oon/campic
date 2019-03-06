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
#include "Object.hpp"

class BossSkill
{
public:
	BossSkill(std::string path, Object* obj, Object* player);
	bool Initialize(Object* obj);
	void Update(float dt);
	void Delete();


	float GetAccountTime();
	float SetAccountTime(float set_account);
	float GetLifeTime();
	float SetLifeTime(float set_life);
	bool IsDead() { return isdead; }


	Object* GetFireObject() { return skill_obj; }

private:
	vector2 random_velocity;

private:
	float live_time = 5.0f;

	vector2 static_random_velocity;

	void UpdateDirection(float dt);
	void SetRandomDirection();
	
	Object* skill_obj = nullptr;
	Object* m_boss = nullptr;
	Object* m_player = nullptr;

	float account_time;
	bool isdead = false;
};
