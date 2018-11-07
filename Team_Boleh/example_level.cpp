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
	for (std::map<std::string, std::unique_ptr<Object>>::iterator it = GetObjectManager()->GetObjectMap().begin(); it != GetObjectManager()->GetObjectMap().end(); ++it)
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
	GetObjectManager()->AddObject("player");
	GetObjectManager()->AddObject("convex_object");
	GetObjectManager()->AddObject("sonic_animation");
        GetObjectManager()->AddObject("dr_strange");
	GetObjectManager()->AddObject("BackGround");

	GetObjectManager()->FindObject("player")->SetScale({ 150.0f, 150.0f });
	GetObjectManager()->FindObject("player")->SetTranslation({ 0, 0 });
	GetObjectManager()->FindObject("player")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	GetObjectManager()->FindObject("player")->AddComponent(new Animation("asset/action.png", "zelda_down", 10, 0.25));
	GetObjectManager()->FindObject("player")->AddComponent(new RigidBody());
	GetObjectManager()->FindObject("player")->GetComponentByTemplate<Animation>()->AddAnimaition("asset/action_c.png", "zelda_up", 10, 0.1f);
	GetObjectManager()->FindObject("player")->AddComponent(new Collision(box_));
	GetObjectManager()->FindObject("player")->AddComponent(new Character(ObjectType::player));

	GetObjectManager()->FindObject("convex_object")->SetScale({ 150.0f, 150.0f });
	GetObjectManager()->FindObject("convex_object")->SetTranslation({ -300, 300 });
	GetObjectManager()->FindObject("convex_object")->SetMesh(mesh::CreateConvex(1, { 255,0,0,255 }));
	GetObjectManager()->FindObject("convex_object")->AddComponent(new RigidBody());

	GetObjectManager()->FindObject("sonic_animation")->SetScale({ 150, 150 });
	GetObjectManager()->FindObject("sonic_animation")->SetTranslation({ 0, -200 });
	GetObjectManager()->FindObject("sonic_animation")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	GetObjectManager()->FindObject("sonic_animation")->AddComponent(new Animation("asset/example2.png", "sonic", 10, 0.25));
	GetObjectManager()->FindObject("sonic_animation")->AddComponent(new RigidBody());
	GetObjectManager()->FindObject("sonic_animation")->AddComponent(new Collision(box_));
	GetObjectManager()->FindObject("sonic_animation")->AddComponent(new Character(ObjectType::wall));

        GetObjectManager()->FindObject("dr_strange")->SetScale({ 150,150 });
        GetObjectManager()->FindObject("dr_strange")->SetTranslation({ -200, -150 });
        GetObjectManager()->FindObject("dr_strange")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	GetObjectManager()->FindObject("dr_strange")->SetDepth(0.5);
        GetObjectManager()->FindObject("dr_strange")->AddComponent(new Sprite());
        GetObjectManager()->FindObject("dr_strange")->GetComponentByTemplate<Sprite>()->Texture_Load("asset/Dr_Strange.png");
	GetObjectManager()->FindObject("dr_strange")->AddComponent(new RigidBody());
	GetObjectManager()->FindObject("dr_strange")->AddComponent(new Collision(box_));
	GetObjectManager()->FindObject("dr_strange")->AddComponent(new Character(ObjectType::wall));

	GetObjectManager()->FindObject("BackGround")->SetScale(GetStateScreenSize());
	GetObjectManager()->FindObject("BackGround")->SetTranslation({0,0});
	GetObjectManager()->FindObject("BackGround")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	GetObjectManager()->FindObject("BackGround")->SetDepth(0.9f);
	GetObjectManager()->FindObject("BackGround")->AddComponent(new Sprite());
	GetObjectManager()->FindObject("BackGround")->GetComponentByTemplate<Sprite>()->Texture_Load("asset/check_background.png");

	GetWorldPhyics()->Gravity_on(GetObjectManager());
}

void example::Update(float dt)
{
	if (Input::IsKeyTriggered(GLFW_KEY_2))
		ChangeLevel("test");

	//Should Fixed this
	GetObjectManager()->FindObject("BackGround")->SetScale(GetStateScreenSize());

	if(dot(GetObjectManager()->FindObject("player")->GetComponentByTemplate<RigidBody>()->GetVelocity(), vector2(0, 1)) > 0)
		GetObjectManager()->FindObject("player")->GetComponentByTemplate<Animation>()->ChangeAnimation("zelda_up");
	else
		GetObjectManager()->FindObject("player")->GetComponentByTemplate<Animation>()->ChangeAnimation("zelda_down");

	GetObjectManager()->FindObject("player")->GetComponentByTemplate<Animation>()->Update(dt);
	GetObjectManager()->FindObject("sonic_animation")->GetComponentByTemplate<Animation>()->Update(dt);

	
	GetWorldPhyics()->Movement_Velocity(*GetObjectManager()->FindObject("player"));
	

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

	move_convex_object(dt, GetObjectManager()->FindObject("convex_object").get());
	GetObjectManager()->FindObject("convex_object")->GetComponentByTemplate<RigidBody>()->Update(dt);
	if(Input::IsKeyPressed(GLFW_KEY_SPACE))
	{
		blackhole(GetObjectManager()->FindObject("player").get(),GetObjectManager()->FindObject("BackGround").get());
	}
	GetObjectManager()->FindObject("player")->GetComponentByTemplate<Animation>()->Update(dt);

	GetObjectManager()->FindObject("sonic_animation")->GetComponentByTemplate<Animation>()->Update(dt);
	
}

void example::ShutDown()
{
	UnLoad();
}

vector2 multi_plus(Object *ob, size_t i)
{
    float x_ = (static_cast<vector2>(ob->GetMesh().GetPoint(i)).x * ob->GetTransform().GetScale().x) + ob->GetTransform().GetTranslation().x;
    float y_ = (static_cast<vector2>(ob->GetMesh().GetPoint(i)).y * ob->GetTransform().GetScale().y) + ob->GetTransform().GetTranslation().y;
    return (x_,y_);
}
