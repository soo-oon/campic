#include "statemanager_test.hpp"
#include "Input.hpp"
#include "Sprite.hpp"
#include "Collision.hpp"


void test_statemanager::Initialize()
{
	Load();
	GetObjectManager()->AddObject("collision");

	GetObjectManager()->FindObject("collision")->SetScale({ 150,150 });
	GetObjectManager()->FindObject("collision")->SetTranslation({});
	GetObjectManager()->FindObject("collision")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	GetObjectManager()->FindObject("collision")->SetDepth(0);
	GetObjectManager()->FindObject("collision")->AddComponent(new Sprite());
	GetObjectManager()->FindObject("collision")->GetComponentByTemplate<Sprite>()->Texture_Load("asset/Dr_Strange.png");
	GetObjectManager()->FindObject("collision")->AddComponent(new Collision(CollisionType::box_, { 0,0 }, { 300,150 }));
}

void test_statemanager::Update(float dt)
{
	GetObjectManager()->FindObject("collision")->GetComponentByTemplate<Collision>()->Update(dt);

	if (Input::IsKeyTriggered(GLFW_KEY_1))
		ChangeLevel("example");
}

void test_statemanager::ShutDown()
{
	UnLoad();
}
