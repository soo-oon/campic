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
#include "Status.hpp"
#include <iostream>
#include "Graphics.hpp"

bool Player::Initialize(Object * Ob)
{
	if (object == nullptr)
	{
		object = Ob;
		object->SetTranslation({ 0,0 });
		object->SetScale({ 100.0f, 100.0f });
		object->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
		object->AddComponent(new RigidBody());
		object->AddComponent(new Sprite("asset/images/Player.png"));
		//object->AddComponent(new Animation("asset/images/Player.png", "player", 8, 0.05f));
		//object->GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/attack.png", "attack", 4, 0.1f, false);
		object->AddComponent(new Collision(box_, {}, { 100.0f, 100.0f }));
		object->AddComponent(new Status(ObjectType::Player, 5, 1, 1.f));

		/*for(auto temp : object->GetComponent())
		{
			temp->Initialize(object);
		}*/
	}
	return true;
}

void Player::Update(float dt)
{
	//MovePlayer();
	//PlayerMove(Input::GetMousePos(Graphics::checking_zoom));
}

void Player::Delete()
{
}

void Player::MovePlayer()
{
	/*std::cout << object->GetTransform().GetTranslation().x << ", " << object->GetTransform().GetTranslation().y
		<< std::endl;*/

	if(object != Objectmanager_.GetObjectMap()[0].get())
	{
		std::cout << "hi" << std::endl;
	}

	if (Input::IsKeyPressed(GLFW_KEY_W))
	{
		object->GetComponentByTemplate<RigidBody>()->AddVelocity(vector2(0, 2));
	}
	if (Input::IsKeyPressed(GLFW_KEY_A))
	{
		object->GetComponentByTemplate<RigidBody>()->AddVelocity(vector2(-2, 0));
	}
	if (Input::IsKeyPressed(GLFW_KEY_S))
	{
		object->GetComponentByTemplate<RigidBody>()->AddVelocity(vector2(0, -2));
	}
	if (Input::IsKeyPressed(GLFW_KEY_D))
	{
		object->GetComponentByTemplate<RigidBody>()->AddVelocity(vector2(2, 0));
	}

	if (Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
	{
		object->GetComponentByTemplate<Animation>()->ChangeAnimation("attack","player");
	}

	/*if (dot(object->GetComponentByTemplate<RigidBody>()->GetVelocity(), vector2(1, 0)) > 0)
	{
		object->GetComponentByTemplate<Animation>()->ChangeAnimation("player");
		object->GetComponentByTemplate<Animation>()->GetCurrentAnimation().sprites->Flip_Not();
	}
	else
	{
		object->GetComponentByTemplate<Animation>()->ChangeAnimation("player");
		object->GetComponentByTemplate<Animation>()->GetCurrentAnimation().sprites->Flip();
	}*/

}

void Player::SetCardList(std::string card)
{
	card_list.push_back(card);
}

void Player::ClearCardList()
{
	card_list.clear();
}

std::vector<std::string> Player::GetCardList()
{
	return card_list;
}
