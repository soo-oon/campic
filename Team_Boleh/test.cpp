#include "test.hpp"

void test::Initialize()
{
	Object* font = new Object();

	font->SetTranslation({-150, 150});
	font->AddComponent(new Font("Welcome To Sword Of Souls", "asset/font/default.ttf", Colors::Black));

	Objectmanager_.AddObject(font);
}

void test::Update(float dt)
{
	if(Input::IsKeyTriggered(GLFW_KEY_Q))
	{
		ChangeLevel("remake");
	}
}

void test::ShutDown()
{
	UnLoad();
}
