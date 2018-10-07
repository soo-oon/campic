#include "example_level.hpp"
#include <iostream>
#include "Sprite.hpp"
#include "PhysicsComponent.hpp"
#include "Input.hpp"
#include "WorldPhysics.h"

bool example::Initialize()
{
	object_manager.AddObject("test");
	check  = object_manager.FindObject("test");
	check->AddComponent(new Sprite());
	check->GetComponentByTemplate<Sprite>()->Texture_Load("asset/strange_for_A.png");

	check->SetScale({ 1.0f, 1.0f });
	check->SetTranslation({ 0,0 });
	check->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	check->AddComponent(new Physics());

    return true;
}

void example::Update(float dt)
{
	world_physics->Movement_by_key(*check);
	//world_physics->Movement(*check);
	check->GetComponentByTemplate<Physics>()->Update(dt);
	check->SetTranslation(check->GetComponentByTemplate<Physics>()->GetPosition());
	std::cout << check->GetComponentByTemplate<Physics>()->GetPosition().x << ", " << check->GetComponentByTemplate<Physics>()->GetPosition().y << std::endl;
}

void example::ShutDown()
{
}
