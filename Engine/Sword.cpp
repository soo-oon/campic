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
#include "control_angle.hpp"
#include "Particle_Generator.hpp"
#include "Application.hpp"

Sword::Sword(Object * player)
{
	m_owner = player;
}

bool Sword::Initialize(Object * Ob)
{
	if (object == nullptr)
	{
		object = Ob;
		object->SetTranslation({ 50,0 });
		object->SetScale({ 75.0f, 75.0f });
		object->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
		object->Add_Init_Component(new Sprite("asset/images/trash.png"));
		//object->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/trash.png");
		object->Add_Init_Component(new Collision(box_));
		object->Add_Init_Component(new RigidBody());
		object->Add_Init_Component(new Status(ObjectType::Sword, 5, 1, 1.f));
		object->GetComponentByTemplate<Collision>()->SetRestitutionType(RestitutionType::none);
		object->SetDepth(m_owner->GetTransform().GetDepth() - 0.1f);
		//object->SetParent(&m_owner->GetTransform());
        m_owner->Add_Init_Component((new Particle_Generator(100, 5.0f,
            5.0f, 200, { 0, 0 }, { 0, 5 },
            { 10.0f, 10.0f }, { Application_.GetScreenSize() }, "asset/images/red_soul.png",false)));
	}
	return true;
}

void Sword::Update(float dt)
{
    if (Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
        object->GetComponentByTemplate<Collision>()->ToggleIsDamaged();

    if (m_owner->GetComponentByTemplate<Player>()->GetPoint() >= 100)
    {
        if (Input::IsKeyTriggered(GLFW_KEY_T))
        {
            sword_name = "ice_sword";
            m_owner->GetComponentByTemplate<Particle_Generator>()->ToggleActive();
            m_owner->GetComponentByTemplate<Particle_Generator>()->SetParticle_Fire_Type(Particle_Fire_Type::Integrate);
            m_owner->GetComponentByTemplate<Particle_Generator>()->SetIsRepeat(false);
            m_owner->GetComponentByTemplate<Particle_Generator>()->SetDurationTime(5.0f);

            m_owner->GetComponentByTemplate<Player>()->SetPoint(0);
        }
        if (Input::IsKeyTriggered(GLFW_KEY_H))
        {
            sword_name = "big_sword";
            m_owner->GetComponentByTemplate<Particle_Generator>()->SetPath("asset/images/blue_soul.png");
            m_owner->GetComponentByTemplate<Particle_Generator>()->ToggleActive();
            m_owner->GetComponentByTemplate<Particle_Generator>()->SetParticle_Fire_Type(Particle_Fire_Type::Divergent);
            m_owner->GetComponentByTemplate<Particle_Generator>()->SetIsRepeat(false);
            m_owner->GetComponentByTemplate<Particle_Generator>()->SetDurationTime(5.0f);

            m_owner->GetComponentByTemplate<Player>()->SetPoint(0);
        }
        if(Input::IsKeyTriggered(GLFW_KEY_KP_0))
        {
            sword_name = "ice_sword";
            object->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/Sword/red_sword.png");
            m_owner->GetComponentByTemplate<Player>()->SetPoint(0);
        }
        if (Input::IsKeyTriggered(GLFW_KEY_KP_1))
        {
            sword_name = "ice_sword";
            object->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/Sword/green_sword.png");
            m_owner->GetComponentByTemplate<Player>()->SetPoint(0);
        }
        if (Input::IsKeyTriggered(GLFW_KEY_KP_2))
        {
            sword_name = "ice_sword";
            object->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/Sword/black_sword.png");
            m_owner->GetComponentByTemplate<Player>()->SetPoint(0);
        }
        if (Input::IsKeyTriggered(GLFW_KEY_KP_3))
        {
            sword_name = "ice_sword";
            object->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/Sword/blue_sword.png");
            m_owner->GetComponentByTemplate<Player>()->SetPoint(0);
        }
    }

    if (m_owner->GetComponentByTemplate<Particle_Generator>()->GetIsDone() && sword_name == "ice_sword")
    {
        object->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/ice_sword.png");
        sword_kind_ = Sword_kind::Ice;
        m_owner->GetComponentByTemplate<Particle_Generator>()->SetIsDone(false);
    }
    if (m_owner->GetComponentByTemplate<Particle_Generator>()->GetIsDone() && sword_name == "big_sword")
    {
        object->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/sword.png");
        sword_kind_ = Sword_kind::Big;
        m_owner->GetComponentByTemplate<Particle_Generator>()->SetIsDone(false);
    }

    if (Input::IsKeyTriggered(GLFW_KEY_Y))
    {
        m_owner->GetComponentByTemplate<Player>()->SetPoint(100);
    }
    
	/*
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
	*/

	auto temp = m_owner->GetTransform().GetTranslation();
	vector2 mouse = Input::GetMousePos(Graphics_.camera_zoom);

	direction.x = mouse.x - temp.x;
	direction.y = mouse.y - temp.y;

	float angle = atan2(mouse.y - temp.y, mouse.x - temp.x);
	angle = To_Degree(angle);

	direction = normalize(direction);

	//std::cout << check.x << ", " << check.y << std::endl;


	//object->SetRotation(To_Degree(angle));
	SwordMove(angle);
}

void Sword::SetOwner(Object* player)
{
	m_owner = player;
}

void Sword::Delete()
{
}

void Sword::SwordMove(float angle)
{
	vector2 temp = { m_owner->GetTransform().GetTranslation().x + direction.x * m_owner->GetTransform().GetScale().x,
		m_owner->GetTransform().GetTranslation().y + direction.y * m_owner->GetTransform().GetScale().y };

	object->SetTranslation(temp);
	object->SetRotation(angle);
	/*
	vector2 swing_direction = normalize(vector2(mouse_position.x - owner->GetTransform().GetTranslation().x,
		mouse_position.y - owner->GetTransform().GetTranslation().y));
	object->SetTranslation(vector2(
		owner->GetTransform().GetTranslation().x + swing_direction.x *owner->GetTransform().GetScale().x / 1.5f,
		owner->GetTransform().GetTranslation().y + swing_direction.y *owner->GetTransform().GetScale().y / 1.5f));
	float anglerad = atan2(mouse_position.y - owner->GetTransform().GetTranslation().y, mouse_position.x - owner->GetTransform().GetTranslation().x);
	float angledeg = (180 / 3.14f)* anglerad;
	object->SetRotation(angledeg - 90);
	*/

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
	/*
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
	*/
}
