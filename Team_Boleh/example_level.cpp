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
    objectmanager->AddObject("test");
    objectmanager->AddObject("hi");

    objectmanager->FindObject("test")->SetScale({ 200.0f, 150.0f });
    objectmanager->FindObject("test")->SetTranslation({ 0, 0 });
    objectmanager->FindObject("test")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
    objectmanager->FindObject("test")->AddComponent(new Animation(4, 0.5, "asset/animation_strange.png"));
    objectmanager->FindObject("test")->AddComponent(new Physics());

    objectmanager->FindObject("hi")->SetScale({ 200.0f, 150.0f });
    objectmanager->FindObject("hi")->SetTranslation({ -100, 100 });
    objectmanager->FindObject("hi")->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
    objectmanager->FindObject("hi")->AddComponent(new Sprite());
    objectmanager->FindObject("hi")->AddComponent(new Physics());
    objectmanager->FindObject("hi")->GetComponentByTemplate<Sprite>()->Texture_Load("asset/strange_for_A.png");

    return true;
}

void example::Update(float dt)
{
    world_physics->Movement_by_key(*objectmanager->FindObject("test"));
    objectmanager->FindObject("test")->GetComponentByTemplate<Physics>()->Update(dt);
    objectmanager->FindObject("test")->GetComponentByTemplate<Animation>()->Update(dt);

    objectmanager->FindObject("hi")->GetComponentByTemplate<Physics>()->Update(dt);

    opponent.clear();
    for (size_t i = 0 ; i < objectmanager->FindObject("test")->GetMesh().GetPointCount(); i++)
        opponent.emplace_back(objectmanager->FindObject("test")->GetTransform().GetTRS()*static_cast<vector2>(objectmanager->FindObject("test")->GetMesh().GetPoint(i)));
    mesh_p.clear();
    for (size_t i = 0; i < objectmanager->FindObject("hi")->GetMesh().GetPointCount(); i++)
    {
        mesh_p.emplace_back(objectmanager->FindObject("hi")->GetTransform().GetTRS()*static_cast<vector2>(objectmanager->FindObject("hi")->GetMesh().GetPoint(i)));
        
    }
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
