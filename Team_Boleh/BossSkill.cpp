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
#include "Object.hpp"
#include "Input.hpp"
#include "Graphics.hpp"
#include "Status.hpp"

bool BossSkill::Initialize(Object* obj)
{
	object = obj;
	object->SetMesh(mesh::CreateBox());
	vector2 accel = normalize(vector2(o_boss->GetTransform().GetTranslation().x,
		o_boss->GetTransform().GetTranslation().y));
	object->SetScale({ o_boss->GetTransform().GetScale().x, o_boss->GetTransform().GetScale().y });
	object->SetTranslation({ o_boss->GetTransform().GetTranslation().x, o_boss->GetTransform().GetTranslation().y });
	object->Add_Init_Component(new Collision(box_));
	object->GetComponentByTemplate<Collision>()->ChangeCollisionBoxScale({ o_boss->GetTransform().GetScale().x, o_boss->GetTransform().GetScale().y });
	object->Add_Init_Component(new RigidBody());
	object->GetComponentByTemplate<RigidBody>()->SetVelocity(200 * accel);
	object->Add_Init_Component(new Animation("asset/images/shot.png", "power", 4, 0.25));
	object->Add_Init_Component(new Status(ObjectType::Shooting, 1, 1, 1.f));

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

float BossSkill::GetLifeTime()
{
	return life_time;
}

float BossSkill::SetLifeTime(float set_life)
{
	return life_time = set_life;
}

Object* BossSkill::GetBossPointer()
{
	return o_boss;
}

void BossSkill::Update(float dt)
{
	account_time += dt;
	if (account_time > life_time)
		object->GetComponentByTemplate<Status>()->ObjectDie();
}
void BossSkill::Delete()
{

}