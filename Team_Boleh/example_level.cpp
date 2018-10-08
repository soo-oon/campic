#include "example_level.hpp"
#include <iostream>
#include "Sprite.hpp"
#include "PhysicsComponent.hpp"
#include "Input.hpp"
#include "WorldPhysics.h"
#include "Animation.hpp"

bool example::Initialize()
{
    objectmanager->AddObject("test");
    objectmanager->FindObject("test")->SetScale({ 200.0f, 150.0f });
    objectmanager->FindObject("test")->SetTranslation({ 0, 0 });
    objectmanager->FindObject("test")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));

    objectmanager->FindObject("test")->AddComponent(new Animation(4, 0.5, "asset/animation_strange.png"));
    objectmanager->FindObject("test")->AddComponent(new Physics());

    return true;
}

void example::Update(float dt)
{
    world_physics->Movement_by_key(*objectmanager->FindObject("test"));
    objectmanager->FindObject("test")->GetComponentByTemplate<Physics>()->Update(dt);
    objectmanager->FindObject("test")->SetTranslation(objectmanager->FindObject("test")->GetComponentByTemplate<Physics>()->GetPosition());
    objectmanager->FindObject("test")->GetComponentByTemplate<Animation>()->Update(dt);
}

void example::ShutDown()
{
}
