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
    objectmanager->AddObject("sex");

    objectmanager->FindObject("test")->SetScale({ 200.0f, 150.0f });
    objectmanager->FindObject("test")->SetTranslation({ 0, 0 });
    objectmanager->FindObject("test")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
    objectmanager->FindObject("test")->AddComponent(new Animation(4, 0.5, "asset/animation_strange.png"));
    objectmanager->FindObject("test")->AddComponent(new Physics());

    objectmanager->FindObject("sex")->SetScale({ 200.0f, 150.0f });
    objectmanager->FindObject("sex")->SetTranslation({ -100, 100 });
    objectmanager->FindObject("sex")->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
    objectmanager->FindObject("sex")->AddComponent(new Sprite());
    objectmanager->FindObject("sex")->AddComponent(new Physics());
    objectmanager->FindObject("sex")->GetComponentByTemplate<Sprite>()->Texture_Load("asset/strange_for_A.png");

    return true;
}

void example::Update(float dt)
{
    world_physics->Movement_by_key(*objectmanager->FindObject("test"));
    objectmanager->FindObject("test")->GetComponentByTemplate<Physics>()->Update(dt);
    objectmanager->FindObject("test")->SetTranslation(objectmanager->FindObject("test")->GetComponentByTemplate<Physics>()->GetPosition());
    objectmanager->FindObject("test")->GetComponentByTemplate<Animation>()->Update(dt);

     objectmanager->FindObject("sex")->GetComponentByTemplate<Physics>()->Update(dt);
     objectmanager->FindObject("sex")->SetTranslation(objectmanager->FindObject("sex")->GetComponentByTemplate<Physics>()->GetPosition());

    opponent.clear();
    for (size_t i = 0 ; i < player->GetMesh().GetPointCount(); i++)
        opponent.emplace_back(player->GetTransform().GetTRS()*static_cast<vector2>(player->GetMesh().GetPoint(i)));
    mesh_p.clear();
    for (size_t i = 0; i < check->GetMesh().GetPointCount(); i++)
    {
        mesh_p.emplace_back( check->GetTransform().GetTRS()*static_cast<vector2>(check->GetMesh().GetPoint(i)));
        
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
