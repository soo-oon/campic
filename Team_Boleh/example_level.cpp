#include "example_level.hpp"
#include <iostream>
#include "Sprite.hpp"
#include "RigidBody.hpp"
#include "Input.hpp"
#include "WorldPhysics.h"
#include "Animation.hpp"
#include "Collision.hpp"
#include "vector2.hpp"
#include "Character.hpp"

void example::blackhole(Object* Ob, Object* Ob1)
{
	for (auto it = GetObjectManager()->GetObjectMap().begin();
		it != GetObjectManager()->GetObjectMap().end(); ++it)
	{
		vector2 black = 0;
		float* rotation = it->second.get()->GetTransform().GetRotation();
		if (it->second.get() != Ob && it->second.get() != Ob1)
		{
			black = vector2(it->second.get()->GetTransform().GetTranslation().x - Ob->GetTransform().GetTranslation().x, it->second.get()->GetTransform().GetTranslation().y - Ob->GetTransform().GetTranslation().y);
			black /= 4000;
			for (int i = 0; i < 10; i++)
			{
				it->second.get()->GetTransform().SetTranslation(it->second.get()->GetTransform().GetTranslation() - black );
			}
			*rotation += 10;
			it->second.get()->SetRotation(*rotation);
		}
	}
}

void example::move_convex_object(float dt, Object* Ob)
{
	float velo = 100;
	limit_time += dt;
	if(limit_time > 1.0f)
	{
		pm *= -1;
		velo *= pm;
		Ob->GetComponentByTemplate<RigidBody>()->SetVelocity(vector2(velo, 0));
		limit_time = 0;
		//std::cout << GetObjectManager()->FindObject("convex_object")->GetComponentByTemplate<Physics>()->GetVelocity().x << std::endl;
	}
}

void example::Initialize()
{
	Load();
	player = BuildAndRegisterDynamicObject("player", vector2(0, 0), vector2(100.f, 100.f));
	player->AddComponent(new Animation("asset/images/action.png", "zelda_down", 10, 0.25));
	player->GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/action_c.png", "zelda_up", 10, 0.1f);
	player->AddComponent(new Collision(box_));
	player->AddComponent(new Character(ObjectType::player));

        spark = BuildAndRegisterDynamicObject("spark", vector2(300, 300), vector2(100.f, 100.f));


        dia = BuildAndRegisterDynamicObject("dia", vector2(420, -100), vector2(50, 50.f));
        dia->AddComponent(new Sprite());
        dia->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/dia.png");
        dia->AddComponent(new Collision(box_));
        dia->AddComponent(new Character(ObjectType::card));

        heart = BuildAndRegisterDynamicObject("heart", vector2(420, 100), vector2(50.f, 50.f));
        heart->AddComponent(new Sprite());
        heart->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/heart.png");
        heart->AddComponent(new Collision(box_));
        heart->AddComponent(new Character(ObjectType::card));


	sword = BuildAndRegisterStaticObject("sword", vector2(0, 0), vector2(75, 75));
	sword->AddComponent(new Sprite());
	sword->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/sword.png");
	sword->AddComponent(new Collision(box_));
	sword->GetComponentByTemplate<Collision>()->SetRestitutionType(RestitutionType::none);
	sword->AddComponent(new Character(ObjectType::sword));

	sonic = BuildAndRegisterDynamicObject("sonic", vector2(0, -200), vector2(150.f, 150.f));
	sonic->AddComponent(new Animation("asset/images/example2.png", "sonic", 10, 0.25));
	sonic->AddComponent(new RigidBody());
	sonic->AddComponent(new Collision(box_));
	sonic->GetComponentByTemplate<Collision>()->SetRestitutionType(RestitutionType::stop);
	sonic->AddComponent(new Character(ObjectType::opponent));
	
	dr_s = BuildAndRegisterDynamicObject("dr_s", vector2(-200, -150), vector2(100.f, 100.f));
	dr_s->SetDepth(0.5);
	dr_s->AddComponent(new Sprite());
	dr_s->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/Dr_Strange.png");
	dr_s->AddComponent(new RigidBody());
	dr_s->AddComponent(new Collision(box_));
	dr_s->AddComponent(new Character(ObjectType::wall));
	
	background = BuildAndRegisterDynamicObject("background", vector2(0,0), vector2(150.f, 150.f));
	background->SetDepth(0.9f);
	background->AddComponent(new Sprite());
	background->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/background.png");
	
	GetWorldPhyics()->Gravity_on(GetObjectManager());
}

void example::Update(float dt)
{
	if (Input::IsKeyTriggered(GLFW_KEY_2))
		ChangeLevel("test");

	SwordSwing(Input::GetMousePos(),player, sword);
	Attact(sword);
	
	//Should Fixed this
	GetObjectManager()->FindObject("background")->SetScale(GetStateScreenSize());

	if(dot(GetObjectManager()->FindObject("player")->GetComponentByTemplate<RigidBody>()->GetVelocity(), vector2(0, 1)) > 0)
		GetObjectManager()->FindObject("player")->GetComponentByTemplate<Animation>()->ChangeAnimation("zelda_up");
	else
		GetObjectManager()->FindObject("player")->GetComponentByTemplate<Animation>()->ChangeAnimation("zelda_down");

	GetObjectManager()->FindObject("player")->GetComponentByTemplate<Animation>()->Update(dt);
        GetObjectManager()->FindObject("sonic")->GetComponentByTemplate<Animation>()->Update(dt);

	
	GetWorldPhyics()->Movement_Velocity(*GetObjectManager()->FindObject("player"));
	

        if(Input::IsKeyPressed(GLFW_KEY_Z))
        {
            spark->AddComponent(new Animation("asset/images/sprite.png", "spark", 7, 0.08));
            spark->GetTransform().SetTranslation(sword->GetTransform().GetTranslation());
            GetObjectManager()->FindObject("spark")->GetComponentByTemplate<Animation>()->Update(dt);
        }

        if (Input::IsKeyTriggered(GLFW_KEY_O))
            gravity_up *= 1.5;
        if (Input::IsKeyTriggered(GLFW_KEY_P))
            gravity_up /= 1.5;

            GetWorldPhyics()->Gravity_on(GetObjectManager(), gravity_up);
	if (Input::IsKeyTriggered(GLFW_KEY_0))
		check = !check;

	if(check)
		GetWorldPhyics()->Movement_Velocity(*GetObjectManager()->FindObject("player").get());
	else
		GetWorldPhyics()->Movement_by_key(*GetObjectManager()->FindObject("player").get());

	if(Input::IsKeyPressed(GLFW_KEY_SPACE))
	{
		blackhole(GetObjectManager()->FindObject("player").get(),GetObjectManager()->FindObject("background").get());
	}
	//GetObjectManager()->FindObject("player")->GetComponentByTemplate<Animation>()->Update(dt);

	//GetObjectManager()->FindObject("sonic")->GetComponentByTemplate<Animation>()->Update(dt);
}

void example::ShutDown()
{
	UnLoad();
}

Object* example::BuildAndRegisterStaticObject(std::string object_name, vector2 position, vector2 scale)
{
	GetObjectManager()->AddObject(object_name);
	GetObjectManager()->FindObject(object_name)->SetScale(scale);
	GetObjectManager()->FindObject(object_name)->SetTranslation(position);
	GetObjectManager()->FindObject(object_name)->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	
	//trans form texture, 
	return GetObjectManager()->FindObject(object_name).get();
}
Object* example::BuildAndRegisterDynamicObject(std::string object_name, vector2 position, vector2 scale)
{
	GetObjectManager()->AddObject(object_name);
	GetObjectManager()->FindObject(object_name)->SetScale(scale);
	GetObjectManager()->FindObject(object_name)->SetTranslation(position);
	GetObjectManager()->FindObject(object_name)->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	//GetObjectManager()->FindObject(object_name)->AddComponent(new Sprite());
	GetObjectManager()->FindObject(object_name)->AddComponent(new RigidBody());
	//trans form texture, 
	return GetObjectManager()->FindObject(object_name).get();
}
void example::SwordPosition(std::string player_str, std::string sword_str)
{
	GetObjectManager()->FindObject(sword_str)->SetTranslation(vector2(
		GetObjectManager()->FindObject(player_str)->GetTransform().GetTranslation().x + 150.f,
		GetObjectManager()->FindObject(player_str)->GetTransform().GetTranslation().y));
}
void example::SwordSwing(vector2 mouse_position, Object* player, Object* sword)
{
	vector2 swing_direction = normalize(vector2(mouse_position.x - player->GetTransform().GetTranslation().x,
		mouse_position.y - player->GetTransform().GetTranslation().y));
	sword->SetTranslation(vector2(
		player->GetTransform().GetTranslation().x + swing_direction.x *player->GetTransform().GetScale().x,
		player->GetTransform().GetTranslation().y + swing_direction.y *player->GetTransform().GetScale().y));
        float anglerad = atan2(mouse_position.y - player->GetTransform().GetTranslation().y, mouse_position.x - player->GetTransform().GetTranslation().x);
        float angledeg = (180 / 3.14 )* anglerad;
        sword->SetRotation(angledeg - 90);
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

void example::Attact(Object * object)
{
	if (Input::IsMousePressed(GLFW_MOUSE_BUTTON_LEFT))
		object->GetComponentByTemplate<Collision>()->ToggleIsDamaged();
}