/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Boss.hpp
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
#include "Object.hpp"
#include "time.h"

enum class BossSkillType
{
	ShootOut,
	PopUp
};

//enum class HadCard
//{
//	red,
//	blue,
//	green,
//	black
//};

class Boss : public Component
{
public:
	Boss(BossSkillType skill);
	bool Initialize(Object* boss_obj);
	void Update(float dt);
	void Delete();
	void BossAttack();
	void ShootOutAttack();
	void PopUpAttack();
	void CardDrop();
	float GetTime();
	float SetTime(float set_time);
private:
	float boss_time;
	BossSkillType boss_skill;
};