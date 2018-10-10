#include "example_level.hpp"
#include <iostream>
#include "Sprite.hpp"
#include "PhysicsComponent.hpp"
#include "Input.hpp"
#include "WorldPhysics.h"
#include "Animation.hpp"
#include "Collision.hpp"

bool example::Initialize()
{
    GetObjectManager()->AddObject("test");
	GetObjectManager()->AddObject("test2");
	GetObjectManager()->AddObject("circle");

	GetObjectManager()->FindObject("test")->SetScale({ -150.0f, 150.0f });
	GetObjectManager()->FindObject("test")->SetTranslation({ 0, 0 });
	GetObjectManager()->FindObject("test")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	GetObjectManager()->FindObject("test")->AddComponent(new Animation(4, 0.5, "asset/animation_strange.png"));
	GetObjectManager()->FindObject("test")->AddComponent(new Physics());

	GetObjectManager()->FindObject("test2")->SetScale({ 150.0f, 150.0f });
	GetObjectManager()->FindObject("test2")->SetTranslation({ -100, 100 });
	GetObjectManager()->FindObject("test2")->SetMesh(mesh::CreateConvex(1, { 255,0,0,255 }));
	GetObjectManager()->FindObject("test2")->AddComponent(new Physics());

	GetObjectManager()->FindObject("circle")->SetScale({ 150, 150 });
	GetObjectManager()->FindObject("circle")->SetTranslation({ 0, -200 });
	GetObjectManager()->FindObject("circle")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	GetObjectManager()->FindObject("circle")->AddComponent(new Animation(10, 0.05, "asset/example2.png"));

    return true;
}

void example::Update(float dt)
{
    GetWorldPhyics()->Movement_by_key(*GetObjectManager()->FindObject("test"));
	GetObjectManager()->FindObject("test")->GetComponentByTemplate<Physics>()->Update(dt);
	GetObjectManager()->FindObject("test")->SetTranslation(GetObjectManager()->FindObject("test")->GetComponentByTemplate<Physics>()->GetPosition());
	GetObjectManager()->FindObject("test")->GetComponentByTemplate<Animation>()->Update(dt);

	GetObjectManager()->FindObject("test2")->GetComponentByTemplate<Physics>()->Update(dt);
	GetObjectManager()->FindObject("test2")->SetTranslation(GetObjectManager()->FindObject("test2")->GetComponentByTemplate<Physics>()->GetPosition());

    opponent.clear();
    for (size_t i = 0 ; i <  GetObjectManager()->FindObject("test")->GetMesh().GetPointCount(); i++)
    opponent.emplace_back(GetObjectManager()->FindObject("test")->GetTransform().GetTRS()*static_cast<vector2>(GetObjectManager()->FindObject("test")->GetMesh().GetPoint(i)));
    mesh_p.clear();
    for (size_t i = 0; i <  GetObjectManager()->FindObject("test2")->GetMesh().GetPointCount(); i++)
    {
        mesh_p.emplace_back(GetObjectManager()->FindObject("test2")->GetTransform().GetTRS()*static_cast<vector2>(GetObjectManager()->FindObject("test2")->GetMesh().GetPoint(i)));
        
    }

	if(GetObjectManager()->FindObject("test")->GetComponentByTemplate<Collision>()->intersection_check(mesh_p, opponent))
	{
		GetObjectManager()->FindObject("test2")->GetMesh().ChangeColor({255,0,0,255});
	}
	else
	{
		GetObjectManager()->FindObject("test2")->GetMesh().ChangeColor({ 255,255,255,255 });
	}

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
