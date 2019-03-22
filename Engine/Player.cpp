/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Player.cpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

#include "Player.hpp"
#include "Input.hpp"
#include "RigidBody.hpp"
#include <iostream>
#include "Graphics.hpp"
#include "control_angle.hpp"

bool Player::Initialize(Object * Ob)
{
	if (object == nullptr)
	{
		object = Ob;
		object->SetTranslation({ 100,-150 });
		object->SetScale({ 50.0f, 50.0f });
		object->SetMesh(mesh::CreateBox(1, { 255,255,255, 255 }));
		object->SetDepth(-0.5f);
		object->AddInitComponent(new RigidBody());
		object->AddInitComponent(new Collision(box_));
		object->AddInitComponent(new Animation("asset/images/Enemies/1_Right.png", "player", 5, 0.2f, true));
		object->SetObjectType(ObjectType::Player);
	}
	return true;
}

void Player::Update(float dt)
{
	MovePlayer();
}

void Player::Delete()
{
}

void Player::MovePlayer()
{
	if (Input::IsKeyTriggered(GLFW_KEY_D))
	{
		object->GetComponentByTemplate<Animation>()->SetFlip(false);
		object->GetComponentByTemplate<RigidBody>()->SetVelocity({ 100, 0 });
	}
	if (Input::IsKeyTriggered(GLFW_KEY_S))
	{
		object->GetComponentByTemplate<RigidBody>()->SetVelocity({ 0, -50 });
	}
        if (object->GetComponentByTemplate<RigidBody>()->GetJumping() == false)
        {
            if (Input::IsKeyTriggered(GLFW_KEY_W))
            {
                object->GetComponentByTemplate<Collision>()->SetIsGround(false);
                object->GetComponentByTemplate<RigidBody>()->SetVelocity({ object->GetComponentByTemplate<RigidBody>()->GetVelocity().x,100 });
                object->GetComponentByTemplate<RigidBody>()->SetJumping(true);
            }
        }
	if (Input::IsKeyTriggered(GLFW_KEY_A))
	{
		object->GetComponentByTemplate<Animation>()->SetFlip(true);
		object->GetComponentByTemplate<RigidBody>()->SetVelocity({ -100, 0 });
	}
}
