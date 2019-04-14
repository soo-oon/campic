#include "Level.hpp"
#include "Input.hpp"
#include "UI.hpp"
#include <iostream>

void Level::Initialize()
{
}

void Level::Update(float dt)
{
	if (Input::IsKeyTriggered(GLFW_KEY_0))
		BackToMenu();

	if(Input::IsKeyTriggered(GLFW_KEY_F1))
	{
		GetCaptureLimit() += 10;
	}
}

void Level::ShutDown()
{
	UnLoad();
}
