#include "example_level.hpp"
#include <iostream>
#include "Sprite.hpp"

bool example::Initialize()
{
	check->AddComponent(new Sprite());
	//dynamic_cast<Sprite*>(check.GetComponent(ComponentType::sprite))->Initialize();
	dynamic_cast<Sprite*>(check->GetComponent(ComponentType::sprite))->Texture_Load("asset/strange_for_A.png");

	check->SetScale({ 1.0f,1.0f });	// if coordinate negative, then flip
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
