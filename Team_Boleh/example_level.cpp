#include "example_level.hpp"
#include <iostream>
#include "Sprite.hpp"
#include "PhysicsComponent.hpp"
#include "Input.hpp"
#include "WorldPhysics.h"
#include "Animation.hpp"
#include "Collision.hpp"
#include "vector2.hpp"

void example::blackhole(Object* Ob)
{
	for (std::map<std::string, std::unique_ptr<Object>>::iterator it = GetObjectManager()->GetObjectMap().begin(); it != GetObjectManager()->GetObjectMap().end(); ++it)
	{
		vector2 black = 0;
		float* rotation = it->second.get()->GetTransform().GetRotation();
		if (it->second.get() != Ob)
		{
			black = vector2(it->second.get()->GetTransform().GetTranslation().x - Ob->GetTransform().GetTranslation().x, it->second.get()->GetTransform().GetTranslation().y - Ob->GetTransform().GetTranslation().y);
			black /= 5000;
			for (int i = 0; i < 10; i++)
			{
				it->second.get()->GetTransform().SetTranslation(it->second.get()->GetTransform().GetTranslation() - black );
			}
			*rotation += 10;
			it->second.get()->SetRotation(*rotation);
		}
	}
}

void example::move_enemy(float dt, Object* Ob)
{
	float velo = 100;
	limit_time += dt;
	if(limit_time > 1.0f)
	{
		pm *= -1;
		velo *= pm;
		Ob->GetComponentByTemplate<Physics>()->SetVelocity(vector2(velo, 0));
		limit_time = 0;
		std::cout << GetObjectManager()->FindObject("enemy")->GetComponentByTemplate<Physics>()->GetVelocity().x << std::endl;
	}
}

bool example::Initialize()
{
    GetObjectManager()->AddObject("test");
	GetObjectManager()->AddObject("enemy");
	GetObjectManager()->AddObject("circle");

	GetObjectManager()->FindObject("test")->SetScale({ 150.0f, 150.0f });
	GetObjectManager()->FindObject("test")->SetTranslation({ 0, 0 });
	GetObjectManager()->FindObject("test")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	GetObjectManager()->FindObject("test")->AddComponent(new Animation(4, 0.5, "asset/animation_strange.png"));
	GetObjectManager()->FindObject("test")->AddComponent(new Physics());

	GetObjectManager()->FindObject("enemy")->SetScale({ 150.0f, 150.0f });
	GetObjectManager()->FindObject("enemy")->SetTranslation({ -300, 300 });
	GetObjectManager()->FindObject("enemy")->SetMesh(mesh::CreateConvex(1, { 255,0,0,255 }));
	GetObjectManager()->FindObject("enemy")->AddComponent(new Physics());

	GetObjectManager()->FindObject("circle")->SetScale({ 150, 150 });
	GetObjectManager()->FindObject("circle")->SetTranslation({ 0, -200 });
	GetObjectManager()->FindObject("circle")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	GetObjectManager()->FindObject("circle")->AddComponent(new Animation(10, 0.05, "asset/example2.png"));

	GetWorldPhyics()->Gravity_on(GetObjectManager());
    return true;
}

void example::Update(float dt)
{
	GetObjectManager()->FindObject("test")->GetComponentByTemplate<Animation>()->Update(dt);
	GetObjectManager()->FindObject("circle")->GetComponentByTemplate<Animation>()->Update(dt);
	

	opponent.clear();
	for (size_t i = 0; i < GetObjectManager()->FindObject("test")->GetMesh().GetPointCount(); i++)
		opponent.emplace_back(GetObjectManager()->FindObject("test")->GetTransform().GetTRS()*static_cast<vector2>(GetObjectManager()->FindObject("test")->GetMesh().GetPoint(i)));
	mesh_p.clear();
	for (size_t i = 0; i < GetObjectManager()->FindObject("enemy")->GetMesh().GetPointCount(); i++)
	{
		mesh_p.emplace_back(GetObjectManager()->FindObject("enemy")->GetTransform().GetTRS()*static_cast<vector2>(GetObjectManager()->FindObject("enemy")->GetMesh().GetPoint(i)));
	}	
	static_opponent.clear();
	for (size_t i = 0; i < GetObjectManager()->FindObject("circle")->GetMesh().GetPointCount(); i++)
	{
		static_opponent.emplace_back(GetObjectManager()->FindObject("circle")->GetTransform().GetTRS()*static_cast<vector2>(GetObjectManager()->FindObject("circle")->GetMesh().GetPoint(i)));
	}
	
	GetWorldPhyics()->Movement_by_key(*GetObjectManager()->FindObject("test"));
	if (GetObjectManager()->FindObject("test")->GetComponentByTemplate<Collision>()->intersection_check(static_opponent, opponent))
	{
		//GetObjectManager()->FindObject("test")->GetComponentByTemplate<Physics>()->SetVelocity(-100 *normalize(GetObjectManager()->FindObject("test")->GetComponentByTemplate<Physics>()->GetVelocity()));
		GetWorldPhyics()->Movement_by_key(*GetObjectManager()->FindObject("test").get());
		if(!Input::IsKeyAnyPressed())
		{
			GetObjectManager()->FindObject("test")->GetComponentByTemplate<Physics>()->SetVelocity(0);
			//GetObjectManager()->FindObject("circle")->GetComponentByTemplate<Physics>()->SetVelocity(0);//-2000 * normalize(GetObjectManager()->FindObject("enemy")->GetComponentByTemplate<Physics>()->GetVelocity()));
		}
		else
		{
			if (abs(GetObjectManager()->FindObject("test")->GetComponentByTemplate<Physics>()->GetVelocity().x) > abs(GetObjectManager()->FindObject("test")->GetComponentByTemplate<Physics>()->GetVelocity().y))
			{
				if (dot(direction, GetObjectManager()->FindObject("test")->GetComponentByTemplate<Physics>()->GetVelocity()) > 0) {
					GetObjectManager()->FindObject("test")->GetComponentByTemplate<Physics>()->SetVelocity(0);
				}
			}
			else if (abs(GetObjectManager()->FindObject("test")->GetComponentByTemplate<Physics>()->GetVelocity().x) < abs(GetObjectManager()->FindObject("test")->GetComponentByTemplate<Physics>()->GetVelocity().y))
			{
				if (dot(direction, GetObjectManager()->FindObject("test")->GetComponentByTemplate<Physics>()->GetVelocity()) > 0 ){
					GetObjectManager()->FindObject("test")->GetComponentByTemplate<Physics>()->SetVelocity(0);
				}
			}
			//GetObjectManager()->FindObject("circle")->GetComponentByTemplate<Physics>()->SetVelocity(0);//-20 ));
			GetObjectManager()->FindObject("test")->GetComponentByTemplate<Physics>()->Update(dt);
		}
		GetObjectManager()->FindObject("test")->GetComponentByTemplate<Physics>()->Update(dt);
		//GetObjectManager()->FindObject("circle")->GetComponentByTemplate<Physics>()->Update(dt);
		GetObjectManager()->FindObject("circle")->GetMesh().ChangeColor({255,255,0,255});
	}
	else if (GetObjectManager()->FindObject("test")->GetComponentByTemplate<Collision>()->intersection_check(opponent, mesh_p))
	{
		//GetObjectManager()->FindObject("test")->GetComponentByTemplate<Physics>()->SetVelocity(-100 * normalize(GetObjectManager()->FindObject("test")->GetComponentByTemplate<Physics>()->GetVelocity()));
		GetObjectManager()->FindObject("test")->GetComponentByTemplate<Physics>()->SetVelocity(-vector2(abs(magnitude(GetObjectManager()->FindObject("test")->GetComponentByTemplate<Physics>()->GetVelocity()))* normalize(GetObjectManager()->FindObject("test")->GetComponentByTemplate<Physics>()->GetVelocity())));
		GetObjectManager()->FindObject("enemy")->GetComponentByTemplate<Physics>()->SetVelocity(-vector2(abs(magnitude(GetObjectManager()->FindObject("enemy")->GetComponentByTemplate<Physics>()->GetVelocity()))* normalize(GetObjectManager()->FindObject("test")->GetComponentByTemplate<Physics>()->GetVelocity())));
		GetObjectManager()->FindObject("circle")->GetMesh().ChangeColor({ 255,0,0,255 });
		GetObjectManager()->FindObject("test")->GetComponentByTemplate<Physics>()->Update(dt);
		GetObjectManager()->FindObject("enemy")->GetComponentByTemplate<Physics>()->Update(dt);
	}
	else {
		GetWorldPhyics()->Movement_by_key(*GetObjectManager()->FindObject("test").get());
		direction = normalize(GetObjectManager()->FindObject("test")->GetComponentByTemplate<Physics>()->GetVelocity());
		GetObjectManager()->FindObject("enemy")->GetMesh().ChangeColor({ 255,0,0,255 });
		GetObjectManager()->FindObject("circle")->GetMesh().ChangeColor({ 255,255,255,255 });
		GetObjectManager()->FindObject("test")->GetComponentByTemplate<Physics>()->Update(dt);
	
	}
	move_enemy(dt, GetObjectManager()->FindObject("enemy").get());
	GetObjectManager()->FindObject("enemy")->GetComponentByTemplate<Physics>()->Update(dt);
	if(Input::IsKeyPressed(GLFW_KEY_SPACE))
	{
		blackhole(GetObjectManager()->FindObject("test").get());
	}
	GetObjectManager()->FindObject("test")->GetComponentByTemplate<Animation>()->Update(dt);

	GetObjectManager()->FindObject("circle")->GetComponentByTemplate<Animation>()->Update(dt);
	
}

void example::ShutDown()
{
}

vector2 multi_plus(Object *ob, size_t i)
{
    float x_ = (static_cast<vector2>(ob->GetMesh().GetPoint(i)).x * ob->GetTransform().GetScale().x) + ob->GetTransform().GetTranslation().x;
    float y_ = (static_cast<vector2>(ob->GetMesh().GetPoint(i)).y * ob->GetTransform().GetScale().y) + ob->GetTransform().GetTranslation().y;
    return (x_,y_);
}
