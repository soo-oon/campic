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
		object->SetTranslation({ 0,0 });
		object->SetScale({ 100.0f, 100.0f });
		object->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
		object->SetDepth(-0.1f);
		object->Add_Init_Component(new RigidBody());

		object->Add_Init_Component(new Collision(box_));
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
}

void Player::Delete()
{
}

void Player::MovePlayer()
{
}
