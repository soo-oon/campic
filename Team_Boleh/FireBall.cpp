/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:  FireBall.cpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

#include "FireBall.hpp"
#include "Object.hpp"
#include "Input.hpp"
#include "Graphics.hpp"
#include "Status.hpp"

bool FireBall::Initialize(Object* Ob)
{
	object = Ob;
	object->SetMesh(mesh::CreateBox());
	vector2 a = normalize(vector2(o_sword->GetTransform().GetTranslation().x - o_player->GetTransform().GetTranslation().x,
		o_sword->GetTransform().GetTranslation().y - o_player->GetTransform().GetTranslation().y));

	object->SetRotation(o_sword->GetTransform().GetRotation() + 90);
	object->SetScale({ o_player->GetTransform().GetScale().x,o_player->GetTransform().GetScale().y });
	object->SetTranslation({ o_player->GetTransform().GetTranslation().x, o_player->GetTransform().GetTranslation().y });
	object->AddComponent(new Collision(box_, vector2(o_player->GetTransform().GetTranslation().x, o_player->GetTransform().GetTranslation().y), 
		{ o_player->GetTransform().GetScale().x, o_player->GetTransform().GetScale().y }));
	object->AddComponent(new RigidBody());
	object->GetComponentByTemplate<RigidBody>()->SetVelocity(200 * a);
	object->AddComponent(new Animation("asset/images/shot.png", "power", 4, 0.25));
	object->AddComponent(new Status(ObjectType::Shooting, 1, 1, 1.f));

	return true;
}

void FireBall::Update(float dt)
{
	account_time += dt;
	if (account_time > life_time)
		isdead = true;
}

void FireBall::Delete()
{
}
