#include "example_level.hpp"
#include <iostream>
#include "Sprite.hpp"
#include "PhysicsComponent.hpp"
#include "Input.hpp"

bool example::Initialize()
{
	object_manager.AddObject("test");
	temp = *object_manager.FindObject("test");
	check->AddComponent(new Sprite());
	check->AddComponent(new Physics());
	check->GetComponentByTemplate<Sprite>()->Texture_Load("asset/strange_for_A.png");
	check->GetComponentByTemplate<Physics>()->SetVelocity(vector2(2, 0));

	check->SetScale({ 1.0f, 1.0f });
	check->SetTranslation({ 0,0 });
	check->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));

    return true;
}

void example::Update(float dt)
{


}

void example::ShutDown()
{
}
