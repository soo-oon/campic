/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: BossSkill.cpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : HyunSung Kim
Secondary :
Creation date: 2019/03/06
- End Header ----------------------------------------------------------------
*/
#include "BossSkill.hpp"
#include "Input.hpp"
#include "Graphics.hpp"
#include "Status.hpp"
#include "RandomFunction.hpp"
#include "control_angle.hpp"

BossSkill::BossSkill(std::string path, Object* obj, Object* player)
{
	m_boss = obj;
	m_player = player;

	skill_obj = new Object();
	skill_obj->SetTranslation(m_boss->GetTransform().GetTranslation());
	skill_obj->SetMesh(mesh::CreateBox(1, Colors::White));
	skill_obj->SetScale({ 150, 150 });
	skill_obj->Add_Init_Component(new Animation(path, "shoot", 4, 1.0f));
	//skill_obj->Add_Init_Component(new Collision(CollisionType::box_));
	//skill_obj->Add_Init_Component(new Status(ObjectType::None, 10, 0, 0, true));

	static_random_velocity = { 10,10 };
}

bool BossSkill::Initialize(Object* obj)
{
	if (m_boss == nullptr)
		m_boss = obj;

	SetRandomDirection();

	return true;
}

float BossSkill::GetAccountTime()
{
	return account_time;
}

float BossSkill::SetAccountTime(float set_account)
{
	return account_time = set_account;
}

void BossSkill::UpdateDirection(float dt)
{
	vector2 temp_position = skill_obj->GetTransform().GetTranslation();

	skill_obj->SetTranslation({ temp_position.x + random_velocity.x,
		temp_position.y + random_velocity.y});
}

void BossSkill::SetRandomDirection()
{
	float temp_x_dir = 0.0f, temp_y_dir = 0.0f;

	if (static_random_velocity.x == 0)
	{
		if (static_random_velocity.y > 0)
		{
			temp_x_dir = 0;
			temp_y_dir = RandomNumberGenerator(-static_random_velocity.y, static_random_velocity.y);
		}
		else
		{
			static_random_velocity.y = abs(static_random_velocity.y);
			temp_x_dir = 0;
			temp_y_dir = RandomNumberGenerator(-static_random_velocity.y, static_random_velocity.y);
		}
	}
	else if (static_random_velocity.y == 0)
	{
		if (static_random_velocity.x > 0)
		{
			temp_x_dir = RandomNumberGenerator(-static_random_velocity.x, static_random_velocity.x);
			temp_y_dir = 0;
		}
		else
		{
			static_random_velocity.x = abs(static_random_velocity.x);
			temp_x_dir = RandomNumberGenerator(-static_random_velocity.x, static_random_velocity.x);
			temp_y_dir = 0;
		}
	}
	else
	{
		if (static_random_velocity.x > 0 && static_random_velocity.y > 0)
		{
			temp_x_dir = RandomNumberGenerator(-static_random_velocity.x, static_random_velocity.x);
			temp_y_dir = RandomNumberGenerator(-static_random_velocity.y, static_random_velocity.y);
		}
		else if (static_random_velocity.x < 0)
		{
			static_random_velocity.x = abs(static_random_velocity.x);
			temp_x_dir = RandomNumberGenerator(-static_random_velocity.x, static_random_velocity.x);
			temp_y_dir = RandomNumberGenerator(-static_random_velocity.y, static_random_velocity.y);
		}
		else
		{
			static_random_velocity.y = abs(static_random_velocity.y);
			temp_x_dir = RandomNumberGenerator(-static_random_velocity.x, static_random_velocity.x);
			temp_y_dir = RandomNumberGenerator(-static_random_velocity.y, static_random_velocity.y);
		}
	}

	random_velocity.x = temp_x_dir;
	random_velocity.y = temp_y_dir;

	float angle = To_Degree(atan2(random_velocity.y, random_velocity.x));

	skill_obj->SetRotation(angle);
}

void BossSkill::Update(float dt)
{
	live_time -= dt;
	UpdateDirection(dt);

	if(live_time <= 0)
	{
		isdead = true;
	}
}

void BossSkill::Delete()
{
}