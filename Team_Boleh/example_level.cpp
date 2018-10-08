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
    check = objectmanager->FindObject("test");
	check->SetScale({ 200.0f, 150.0f });
	check->SetTranslation({ 0,0 });
	check->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));

	check->AddComponent(new Animation(4, 0.5, "asset/animation_strange.png"));
	auto a = check->GetTransform();
	check->AddComponent(new Physics());

	//check->AddComponent(new Sprite());
	//check->GetComponentByTemplate<Sprite>()->Texture_Load("asset/animation_strange.png");
	//check->GetComponentByTemplate<Sprite>()->Texture_Load("asset/strange_for_A.png");
	std::cout << a.GetTranslation().x << ", " << a.GetTranslation().y << std::endl;

    return true;
}

void example::Update(float dt)
{
	world_physics->Movement_by_key(*check);
	//world_physics->Movement(*check);
	check->GetComponentByTemplate<Physics>()->Update(dt);
	check->SetTranslation(check->GetComponentByTemplate<Physics>()->GetPosition());
	check->GetComponentByTemplate<Animation>()->Update(dt);

	std::cout << check->GetComponentByTemplate<Physics>()->GetPosition().x << ", " << check->GetComponentByTemplate<Physics>()->GetPosition().y << std::endl;
}

void example::ShutDown()
{
}
