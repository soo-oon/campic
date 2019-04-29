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
		object->SetScale({ 80.0f, 80.f });
		object->SetMesh(mesh::CreateBox(1, { 255,255,255, 255 }));
		object->SetDepth(-0.6f);
		object->SetObjectType(ObjectType::Player);
		object->AddInitComponent(new Animation("asset/images/Player_Animation.png", "player", 8, 0.05f, true));
		object->AddInitComponent(new RigidBody());
		object->AddInitComponent(new Collision(box_));
		object->GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/Player_Capture.png", "capture", 4, 0.01f, false);
		object->GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/Player_Jump.png", "jump", 12, 0.01f, false);
	}
	return true;
}

void Player::Update(float dt)
{
#ifdef _DEBUG
#else 
    if (auto camera = Graphics_.GetCurrentCamera();
        camera != nullptr)
    {
        camera->SetCenter(object->GetTransform().GetTranslation());
    }

#endif
	MouseTest();
}

void Player::Delete()
{
}

void Player::MouseTest()
{
	vector2 current_mouse_pos = Input::GetMousePos();

	if (prev_mouse_pos != current_mouse_pos)
	{
		offset = {};
		save_pos = object->GetTransform().GetTranslation();
		prev_mouse_pos = current_mouse_pos;
	}
	else
	{
		offset = object->GetTransform().GetTranslation() - save_pos;

		//std::cout << offset.x << ", " << offset.y << std::endl;
	}
}
