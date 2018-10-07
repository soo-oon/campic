#include "example_level.hpp"
#include <iostream>
#include "Sprite.hpp"
#include "PhysicsComponent.hpp"
#include "Input.hpp"

bool example::Initialize()
{
	object_manager.AddObject("test");
	temp = *object_manager.FindObject("test");
	temp.AddComponent(new Sprite());
	temp.AddComponent(new Physics());
	//dynamic_cast<Sprite*>(check.GetComponent(ComponentType::sprite))->Initialize();
	temp.GetComponentByTemplate<Sprite>()->Texture_Load("asset/strange_for_A.png");
	temp.GetComponentByTemplate<Physics>()->SetVelocity(vector2(2, 0));

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
