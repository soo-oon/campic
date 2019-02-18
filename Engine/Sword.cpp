/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Sword.cpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary : Jung Soon Woo
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

#include "Sword.hpp"
#include "Input.hpp"
#include "Graphics.hpp"
#include "Status.hpp"
#include <iostream>
#include "Player.hpp"

Sword::Sword(Object * player)
{
	owner = player;
}

bool Sword::Initialize(Object * Ob)
{
	if (object == nullptr)
	{
		object = Ob;
		auto temp_translation = owner->GetTransform().GetTranslation();
		object->SetScale({ 75.0f, 75.0f });
		object->SetTranslation(temp_translation);
		object->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
		object->AddComponent(new Sprite("asset/images/trash.png"));
		//object->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/trash.png");
		object->AddComponent(new Collision(box_, {}, { 40.0f, 40.0f }));
		object->AddComponent(new RigidBody());
		object->GetComponentByTemplate<Collision>()->SetRestitutionType(RestitutionType::none);
		object->AddComponent(new Status(ObjectType::Sword));
		object->SetDepth(0.978f);
	}
	return true;
}

void Sword::Update(float dt)
{
	/*std::cout << owner->GetTransform().GetTranslation().x << ", " <<
		owner->GetTransform().GetTranslation().y << std::endl;
		*/

    if(Input::IsKeyPressed(GLFW_KEY_T))
    {
        if (
            owner->GetComponentByTemplate<Player>()->GetCardList().size() == 1)
        {
            sword_name = "ice_sword";
            object->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/ice_sword.png");
        }
        else
        {
            sword_name = "sword";
            object->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/sword.png");
        }
    }
	if (sword_name == "trash")
	{
		if (Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
		{
			object->GetComponentByTemplate<Collision>()->ToggleIsDamaged();
		}
	}
	else if (sword_name == "ice_sword")
	{
		if (Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
			object->GetComponentByTemplate<Collision>()->ToggleIsDamaged();
		if (Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_RIGHT))
		{
			skill = true;
			object->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/picture2.png");
			owner->GetComponentByTemplate<Animation>()->ChangeAnimation("attack");
		}
		else
		{
			//owner->GetComponentByTemplate<Animation>()->ChangeAnimation("player");
		}
	}
	else if(sword_name == "sword")
	{
		if (Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
			object->GetComponentByTemplate<Collision>()->ToggleIsDamaged();
	}
	if (!skill)
		SwordMove(Input::GetMousePos(Graphics::camera_zoom));
	else
		Wheelwind();
}

void Sword::SetOwner(Object* player)
{
	owner = player;
}

void Sword::Delete()
{
}

void Sword::SwordMove(vector2 mouse_position)
{
	vector2 swing_direction = normalize(vector2(mouse_position.x - owner->GetTransform().GetTranslation().x,
		mouse_position.y - owner->GetTransform().GetTranslation().y));
	object->SetTranslation(vector2(
		owner->GetTransform().GetTranslation().x + swing_direction.x *owner->GetTransform().GetScale().x / 1.5f,
		owner->GetTransform().GetTranslation().y + swing_direction.y *owner->GetTransform().GetScale().y / 1.5f));
	float anglerad = atan2(mouse_position.y - owner->GetTransform().GetTranslation().y, mouse_position.x - owner->GetTransform().GetTranslation().x);
	float angledeg = (180 / 3.14f)* anglerad;
	object->SetRotation(angledeg - 90);
	//sword->GetComponentByTemplate<Collision>()->GetCollisionTransform().SetRotation(angledeg - 90);
//float a = dot(sword->GetTransform().GetTranslation(), vector2(0, 1))/ magnitude(sword->GetTransform().GetTranslation());
//if(mouse_position.x > player->GetTransform().GetTranslation().x)
//{
//    std::cout <<"mouse : "<< mouse_position.x <<"player : " << player->GetTransform().GetTranslation().x << std::endl;
//    a = 360 - acos(a)*(180 / 3.14);
//}
//else
//a = acos(a)*(180/3.14);
//std::cout << a << std::endl;
//sword->SetRotation(a);
}

void Sword::SetName(std::string sword_string)
{
	sword_name = sword_string;
}

std::string Sword::GetName()
{
	return sword_name;
}

void Sword::Wheelwind()
{
	float x_vel, y_vel;
	angle -= 10;
	if (angle > -360) {
		//card_velo -= 0.5f;
		x_vel = cos(angle)*(20) + sin(angle)*(20);
		y_vel = -sin(angle)*(20) + cos(angle)*(20);
		object->GetTransform().SetTranslation(vector2(owner->GetTransform().GetTranslation().x - 3 * x_vel, owner->GetTransform().GetTranslation().y - 3 * y_vel));
		object->SetRotation(angle * 20);
		object->GetComponentByTemplate<Collision>()->ToggleIsDamaged();
	}
	else {
		angle = 0;
		skill = false;
		object->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/ice_sword.png");
	}
}
