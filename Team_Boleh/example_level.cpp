#include "example_level.hpp"
#include <iostream>
#include "Sprite.hpp"

bool example::Initialize()
{
	temp.AddComponent(new Sprite());
	//dynamic_cast<Sprite*>(check.GetComponent(ComponentType::sprite))->Initialize();
	dynamic_cast<Sprite*>(temp.GetComponent(ComponentType::sprite))->Texture_Load("asset/strange_for_A.png");

	Transform temp_;
	temp_.SetScale({ 1.0f, 1.0f });
	temp_.SetTranslation({ 0,0 });

	temp.SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	temp.SetTransform(temp_);

	check = &temp;


    return true;
}

void example::Update(float dt)
{
}

void example::ShutDown()
{
}
