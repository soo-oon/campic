#include "statemanager_test.hpp"
#include "Input.hpp"
#include "Sprite.hpp"
#include "Collision.hpp"
#include "Camera.hpp"
#include "Animation.hpp"
#include <iostream>

void test_statemanager::Initialize()
{
	Load();
	GetObjectManager()->AddObject("camera");
	GetObjectManager()->AddObject("test1");
	GetObjectManager()->AddObject("test2");
	GetObjectManager()->AddObject("test3");
	GetObjectManager()->AddObject("test4");
	GetObjectManager()->AddObject("test5");
	GetObjectManager()->AddObject("test6");
	GetObjectManager()->AddObject("test7");
	GetObjectManager()->AddObject("test8");
	GetObjectManager()->AddObject("test9");
	GetObjectManager()->AddObject("test10");
	GetObjectManager()->AddObject("test11");
	GetObjectManager()->AddObject("test12");
	GetObjectManager()->AddObject("test13");
	GetObjectManager()->AddObject("test14");
	GetObjectManager()->AddObject("test15");
	GetObjectManager()->AddObject("test16");
	GetObjectManager()->AddObject("test17");
	GetObjectManager()->AddObject("test18");
	GetObjectManager()->AddObject("test19");

	//GetObjectManager()->AddObject("camera");

	GetObjectManager()->FindObject("camera")->SetScale({ 10,10 });
	GetObjectManager()->FindObject("camera")->SetTranslation({ 0,0 });
	GetObjectManager()->FindObject("camera")->AddComponent(new Camera());

	GetObjectManager()->FindObject("test1")->SetScale({ 150,150 });
	GetObjectManager()->FindObject("test1")->SetTranslation({-100,0});
	GetObjectManager()->FindObject("test1")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	GetObjectManager()->FindObject("test1")->SetDepth(0);
	GetObjectManager()->FindObject("test1")->AddComponent(new Animation("asset/action.png", "zelda_down", 10, 0.25));
	GetObjectManager()->FindObject("test1")->AddComponent(new Collision(CollisionType::box_, { 0,0 }, { 150,150 }));

	GetObjectManager()->FindObject("test2")->SetScale({ 150,150 });
	GetObjectManager()->FindObject("test2")->SetTranslation({-90,0});
	GetObjectManager()->FindObject("test2")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	GetObjectManager()->FindObject("test2")->SetDepth(0);
	GetObjectManager()->FindObject("test2")->AddComponent(new Animation("asset/action.png", "zelda_down", 10, 0.25));

	GetObjectManager()->FindObject("test3")->SetScale({ 150,150 });
	GetObjectManager()->FindObject("test3")->SetTranslation({-80,0});
	GetObjectManager()->FindObject("test3")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	GetObjectManager()->FindObject("test3")->SetDepth(0);
	GetObjectManager()->FindObject("test3")->AddComponent(new Animation("asset/action.png", "zelda_down", 10, 0.25));

	GetObjectManager()->FindObject("test4")->SetScale({ 150,150 });
	GetObjectManager()->FindObject("test4")->SetTranslation({-70,0});
	GetObjectManager()->FindObject("test4")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	GetObjectManager()->FindObject("test4")->SetDepth(0);
	GetObjectManager()->FindObject("test4")->AddComponent(new Animation("asset/action.png", "zelda_down", 10, 0.25));

	GetObjectManager()->FindObject("test5")->SetScale({ 150,150 });
	GetObjectManager()->FindObject("test5")->SetTranslation({-60, 0});
	GetObjectManager()->FindObject("test5")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	GetObjectManager()->FindObject("test5")->SetDepth(0);
	GetObjectManager()->FindObject("test5")->AddComponent(new Animation("asset/action.png", "zelda_down", 10, 0.25));

	GetObjectManager()->FindObject("test6")->SetScale({ 150,150 });
	GetObjectManager()->FindObject("test6")->SetTranslation({-50 , 0});
	GetObjectManager()->FindObject("test6")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	GetObjectManager()->FindObject("test6")->SetDepth(0);
	GetObjectManager()->FindObject("test6")->AddComponent(new Animation("asset/action.png", "zelda_down", 10, 0.25));

	GetObjectManager()->FindObject("test7")->SetScale({ 150,150 });
	GetObjectManager()->FindObject("test7")->SetTranslation({-40 ,0});
	GetObjectManager()->FindObject("test7")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	GetObjectManager()->FindObject("test7")->SetDepth(0);
	GetObjectManager()->FindObject("test7")->AddComponent(new Animation("asset/action.png", "zelda_down", 10, 0.25));

	GetObjectManager()->FindObject("test8")->SetScale({ 150,150 });
	GetObjectManager()->FindObject("test8")->SetTranslation({-30 ,0});
	GetObjectManager()->FindObject("test8")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	GetObjectManager()->FindObject("test8")->SetDepth(0);
	GetObjectManager()->FindObject("test8")->AddComponent(new Animation("asset/action.png", "zelda_down", 10, 0.25));

	GetObjectManager()->FindObject("test9")->SetScale({ 150,150 });
	GetObjectManager()->FindObject("test9")->SetTranslation({});
	GetObjectManager()->FindObject("test9")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	GetObjectManager()->FindObject("test9")->SetDepth(0);
	GetObjectManager()->FindObject("test9")->AddComponent(new Animation("asset/action.png", "zelda_down", 10, 0.25));

	GetObjectManager()->FindObject("test10")->SetScale({ 150,150 });
	GetObjectManager()->FindObject("test10")->SetTranslation({-20, 0});
	GetObjectManager()->FindObject("test10")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	GetObjectManager()->FindObject("test10")->SetDepth(0);
	GetObjectManager()->FindObject("test10")->AddComponent(new Animation("asset/action.png", "zelda_down", 10, 0.25));

	GetObjectManager()->FindObject("test11")->SetScale({ 150,150 });
	GetObjectManager()->FindObject("test11")->SetTranslation({-10 , 0});
	GetObjectManager()->FindObject("test11")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	GetObjectManager()->FindObject("test11")->SetDepth(0);
	GetObjectManager()->FindObject("test11")->AddComponent(new Animation("asset/action.png", "zelda_down", 10, 0.25));

	GetObjectManager()->FindObject("test12")->SetScale({ 150,150 });
	GetObjectManager()->FindObject("test12")->SetTranslation({});
	GetObjectManager()->FindObject("test12")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	GetObjectManager()->FindObject("test12")->SetDepth(0);
	GetObjectManager()->FindObject("test12")->AddComponent(new Animation("asset/action.png", "zelda_down", 10, 0.25));

	GetObjectManager()->FindObject("test13")->SetScale({ 150,150 });
	GetObjectManager()->FindObject("test13")->SetTranslation({10, 0});
	GetObjectManager()->FindObject("test13")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	GetObjectManager()->FindObject("test13")->SetDepth(0);
	GetObjectManager()->FindObject("test13")->AddComponent(new Animation("asset/action.png", "zelda_down", 10, 0.25));

	GetObjectManager()->FindObject("test14")->SetScale({ 150,150 });
	GetObjectManager()->FindObject("test14")->SetTranslation({20,0 });
	GetObjectManager()->FindObject("test14")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	GetObjectManager()->FindObject("test14")->SetDepth(0);
	GetObjectManager()->FindObject("test14")->AddComponent(new Animation("asset/action.png", "zelda_down", 10, 0.25));

	GetObjectManager()->FindObject("test15")->SetScale({ 150,150 });
	GetObjectManager()->FindObject("test15")->SetTranslation({30, 0});
	GetObjectManager()->FindObject("test15")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	GetObjectManager()->FindObject("test15")->SetDepth(0);
	GetObjectManager()->FindObject("test15")->AddComponent(new Animation("asset/action.png", "zelda_down", 10, 0.25));

	GetObjectManager()->FindObject("test16")->SetScale({ 150,150 });
	GetObjectManager()->FindObject("test16")->SetTranslation({40,0 });
	GetObjectManager()->FindObject("test16")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	GetObjectManager()->FindObject("test16")->SetDepth(0);
	GetObjectManager()->FindObject("test16")->AddComponent(new Animation("asset/action.png", "zelda_down", 10, 0.25));

	GetObjectManager()->FindObject("test17")->SetScale({ 150,150 });
	GetObjectManager()->FindObject("test17")->SetTranslation({50, 0});
	GetObjectManager()->FindObject("test17")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	GetObjectManager()->FindObject("test17")->SetDepth(0);
	GetObjectManager()->FindObject("test17")->AddComponent(new Animation("asset/action.png", "zelda_down", 10, 0.25));

	GetObjectManager()->FindObject("test18")->SetScale({ 150,150 });
	GetObjectManager()->FindObject("test18")->SetTranslation({60, 0});
	GetObjectManager()->FindObject("test18")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	GetObjectManager()->FindObject("test18")->SetDepth(0);
	GetObjectManager()->FindObject("test18")->AddComponent(new Animation("asset/action.png", "zelda_down", 10, 0.25));

	GetObjectManager()->FindObject("test19")->SetScale({ 150,150 });
	GetObjectManager()->FindObject("test19")->SetTranslation({70,0 });
	GetObjectManager()->FindObject("test19")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	GetObjectManager()->FindObject("test19")->SetDepth(0);
	GetObjectManager()->FindObject("test19")->AddComponent(new Animation("asset/action.png", "zelda_down", 10, 0.25));

	//GetObjectManager()->FindObject("camera")->SetTranslation({});
	//GetObjectManager()->FindObject("camera")->AddComponent(new Camera());
}

void test_statemanager::Update(float dt)
{
	if (Input::IsKeyTriggered(GLFW_KEY_1))
		ChangeLevel("example");

	/*if(Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_RIGHT))
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
		check2 = !check2;
		if(check2)
		{
			GetObjectManager()->FindObject("collision")->GetComponentByTemplate<Collision>()->GetCollsionMesh().Visible();
		}
		else
		{
			GetObjectManager()->FindObject("collision")->GetComponentByTemplate<Collision>()->GetCollsionMesh().Invisible();
		}
	}*/
}

void test_statemanager::ShutDown()
{
	UnLoad();
}
