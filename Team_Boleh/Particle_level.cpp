#include "Particle_level.hpp"
#include "Input.hpp"
#include "Sprite.hpp"
#include "Particle.hpp"
#include <iostream>

void Particle_level::Initialize()
{
	/*GetObjectManager()->AddObject("Player");

	GetObjectManager()->FindObject("Player")->SetScale({ 100.0f, 100.0f });
	GetObjectManager()->FindObject("Player")->SetTranslation({ 0,0 });
	GetObjectManager()->FindObject("Player")->SetMesh(mesh::CreateBox(1, { 255,255,255 }));
	GetObjectManager()->FindObject("Player")->AddComponent(new Sprite());
	GetObjectManager()->FindObject("Player")->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/Dr_Strange.png");
	*/
	GetObjectManager()->FindObject("Player")->AddComponent(new Particle(100, 0.1f, 101, { 0.0f, 0.0f }));
	GetObjectManager()->FindObject("Player")->GetComponentByTemplate<Particle>()->Particle_Generate(
		GetObjectManager()->FindObject("Player")->GetTransform(), mesh::CreateBox(1, { 255,255,255 }),
		5.0f, "asset/images/Basketball.png");

	
}

void Particle_level::Update(float dt)
{
	if (Input::IsKeyTriggered(GLFW_KEY_1))
		ChangeLevel("example");
	if (Input::IsKeyTriggered(GLFW_KEY_2))
		ChangeLevel("test");
	if (Input::IsKeyTriggered(GLFW_KEY_3))
		ChangeLevel("MapEditorTest");

	GetObjectManager()->FindObject("Player")->GetComponentByTemplate<Particle>()->Update(dt);
}

void Particle_level::ShutDown()
{
}
