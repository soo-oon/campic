/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Boss.cpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : HyunSung Kim
Secondary :
Creation date: 2019/03/06
- End Header ----------------------------------------------------------------
*/
#include "Boss.hpp"
#include "Card.hpp"
#include "Input.hpp"
#include "Status.hpp"
#include "Timer.hpp"
#include "BossSkill.hpp"
#include "RandomFunction.hpp"

float Boss::GetTime()
{
	return boss_time;
}

float Boss::SetTime(float set_time)
{
	return boss_time = set_time;
}

Boss::Boss(BossSkillType skill)
{
	boss_skill = skill;
}

bool Boss::Initialize(Object* boss_obj)
{
	if(object == nullptr)
		object = boss_obj;
	return false;
}

void Boss::Update(float dt)
{
	boss_time += dt;

	if (boss_time >= 2.0f)
	{
		BossAttack();
		boss_time = 0;
	}

	if (!object->GetComponentByTemplate<Status>()->IsAlive())
	{
		CardDrop();
	}
}

void Boss::Delete()
{

}

void Boss::BossAttack()
{
	switch (boss_skill)
	{
	case BossSkillType::ShootOut:
		ShootOutAttack();
		break;
	case BossSkillType::PopUp:
		PopUpAttack();
		break;
	}
}

void Boss::ShootOutAttack()
{
	Object* attack = new Object();
	attack->AddComponent(new BossSkill(object, 2));

	Objectmanager_.AddObject(attack);

}

void Boss::PopUpAttack()
{
	Object* pop = new Object();

	vector2 boundary = {100, 100};
	boundary.x = RandomNumberGenerator(-boundary.x, boundary.x);
	boundary.y = RandomNumberGenerator(-boundary.y, boundary.y);

	pop->SetTranslation({ boundary });
	pop->SetScale({ 30.0f, 30.0f });
	pop->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	pop->SetDepth(0.0f);
	pop->AddComponent(new Animation("asset/images/shot.png", "power", 4, 0.25));
	pop->AddComponent(new Status(ObjectType::None));

	Objectmanager_.AddObject(pop);

	//if(pop->GetComponentByTemplate<Animation>()->IsDone())

}

void Boss::CardDrop()
{
	Object* card = new Object();
	card->SetTranslation({ object->GetTransform().GetTranslation() });
	card->SetScale({ 24.f, 30.f });
	card->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	card->AddComponent(new Status(ObjectType::Item));
	card->AddComponent(new Collision(box_));
	object->GetComponentByTemplate<Collision>()->ChangeCollisionBoxScale({ 24.f,30.f });
	int random = rand() % 4;
	if (random == 0)
	{
		card->AddComponent(new Sprite("asset/images/red_soul.png"));
		card->AddComponent(new Card("Red"));
	}
	else if (random == 1)
	{
		card->AddComponent(new Sprite("asset/images/blue_soul.png"));
		card->AddComponent(new Card("Blue"));
	}
	else if (random == 2)
	{
		card->AddComponent(new Sprite("asset/images/green_soul.png"));
		card->AddComponent(new Card("Green"));
	}
	else
	{
		card->AddComponent(new Sprite("asset/images/black_soul.png"));
		card->AddComponent(new Card("Black"));
	}
	Objectmanager_.AddObject(card);
}