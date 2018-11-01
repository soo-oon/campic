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
	GetObjectManager()->FindObject("collision")->AddComponent(new Collision(CollisionType::box_, { 0,0 }, { 150,150 }));
}

void test_statemanager::Update(float dt)
{
	GetObjectManager()->FindObject("collision")->GetComponentByTemplate<Collision>()->Update(dt);

	if (Input::IsKeyTriggered(GLFW_KEY_1))
		ChangeLevel("example");

	if(Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_RIGHT))
	{
		check1 = !check1;

		if (!check1)
		{
			GetObjectManager()->FindObject("collision")->GetComponentByTemplate<Sprite>()->Flip();
		}
		else
		{
			GetObjectManager()->FindObject("collision")->GetComponentByTemplate<Sprite>()->Flip_Not();
		}
	}

	if(Input::IsKeyTriggered(GLFW_KEY_SPACE))
	{
		check = !check;
		if(check)
		{
			GetObjectManager()->FindObject("collision")->GetComponentByTemplate<Collision>()->GetCollsionMesh().Visible();
		}
		else
		{
			GetObjectManager()->FindObject("collision")->GetComponentByTemplate<Collision>()->GetCollsionMesh().Invisible();
		}
	}
}

void test_statemanager::ShutDown()
{
	UnLoad();
}
