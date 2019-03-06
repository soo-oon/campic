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
#include "Card.hpp"
#include "control_angle.hpp"

bool Player::Initialize(Object * Ob)
{
	if (object == nullptr)
	{
		object = Ob;
		object->SetTranslation({ 0,0 });
		object->SetScale({ 100.0f, 100.0f });
		object->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
		object->SetDepth(-0.1f);
		object->Add_Init_Component(new RigidBody());

		object->Add_Init_Component(new Animation("asset/images/Player/S.png", "s", 8, 0.05f));
		object->GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/Player/E.png", "e", 8, 0.05f);
		object->GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/Player/W.png", "w", 7, 0.05f);
		object->GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/Player/N.png", "n", 4, 0.05f);
		object->GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/Player/S_E.png", "s_e", 8, 0.05f);
		object->GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/Player/S_W.png", "s_w", 8, 0.05f);
		object->GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/Player/N_E.png", "n_e", 8, 0.05f);
		object->GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/Player/N_W.png", "n_w", 8, 0.05f);

		object->Add_Init_Component(new Collision(box_));
		object->Add_Init_Component(new Status(ObjectType::Player, 500, 1, 1.f));
		object->Add_Init_Component(new Sound("asset/sounds/punch.wav"));

		/*for(auto temp : object->GetComponent())
		{
			temp->Initialize(object);
		}*/
	}
	return true;
}

void Player::Update(float dt)
{
	auto temp = object->GetTransform().GetTranslation();
	vector2 mouse = Input::GetMousePos(Graphics_.camera_zoom);

	direction.x = mouse.x - temp.x;
	direction.y = mouse.y - temp.y;

	float angle = atan2(mouse.y - temp.y, mouse.x - temp.x);
	angle = To_Degree(angle);

	direction = normalize(direction);

	MovePlayer();

	//object->GetComponentByTemplate<Animation>()->ChangeAnimation("e");

	PlayerAnimation(angle);
	//PlayerMove(Input::GetMousePos(Graphics::checking_zoom));
}

void Player::Delete()
{
}

void Player::MovePlayer()
{
    if (Input::IsKeyPressed(GLFW_KEY_V))
    {
        boost = 4;
    }
	else
	{
		boost = 3;
	}


	if (Input::IsKeyPressed(GLFW_KEY_W))
	{
		object->GetComponentByTemplate<RigidBody>()->SetVelocity(vector2(object->GetComponentByTemplate<RigidBody>()->GetVelocity().x, object->GetComponentByTemplate<Status>()->GetSpeed()*24 * boost));
	}
	if (Input::IsKeyPressed(GLFW_KEY_A))
	{
		object->GetComponentByTemplate<RigidBody>()->SetVelocity(vector2(object->GetComponentByTemplate<Status>()->GetSpeed()*-24 * boost, object->GetComponentByTemplate<RigidBody>()->GetVelocity().y));
	}
	if (Input::IsKeyPressed(GLFW_KEY_S))
	{
		object->GetComponentByTemplate<RigidBody>()->SetVelocity(vector2(object->GetComponentByTemplate<RigidBody>()->GetVelocity().x, object->GetComponentByTemplate<Status>()->GetSpeed()* -24 * boost));
	}
	if (Input::IsKeyPressed(GLFW_KEY_D))
	{
		object->GetComponentByTemplate<RigidBody>()->SetVelocity(vector2(object->GetComponentByTemplate<Status>()->GetSpeed() * 24 * boost, object->GetComponentByTemplate<RigidBody>()->GetVelocity().y));
	}
	object->GetComponentByTemplate<RigidBody>()->SetVelocity(object->GetComponentByTemplate<RigidBody>()->GetVelocity() * 0.9f);

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

void Player::PlayerAnimation(float angle)
{
	if(angle <= 22.5f && angle > -22.5f)
	{
		object->GetComponentByTemplate<Animation>()->ChangeAnimation("e");
	}
	else if(angle > 22.5f && angle <= 67.5f)
	{
		object->GetComponentByTemplate<Animation>()->ChangeAnimation("n_e");
	}
	else if(angle > 67.5f && angle <= 112.5f)
	{
		object->GetComponentByTemplate<Animation>()->ChangeAnimation("n");
	}
	else if( angle > 112.5f && angle <=157.5f)
	{
		object->GetComponentByTemplate<Animation>()->ChangeAnimation("n_w");
	}
	else if(angle > 157.5f || angle <= -157.5f)
	{
		object->GetComponentByTemplate<Animation>()->ChangeAnimation("w");
	}
	else if (angle > -157.5f && angle <= -112.5f)
	{
		object->GetComponentByTemplate<Animation>()->ChangeAnimation("s_w");
	}
	else if (angle > -112.5f && angle <= -67.5f)
	{
		object->GetComponentByTemplate<Animation>()->ChangeAnimation("s");
	}
	else if (angle > -67.5f && angle <= -22.5f)
	{
		object->GetComponentByTemplate<Animation>()->ChangeAnimation("s_e");
	}
}
