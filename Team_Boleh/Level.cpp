#include "Level.hpp"
#include "Input.hpp"
#include "UI.hpp"
#include <iostream>

void Level::Initialize()
{
}

void Level::Update(float dt)
{
	if (Input::IsKeyTriggered(GLFW_KEY_F2))
		BackToMenu();

	if(Input::IsKeyTriggered(GLFW_KEY_F1))
	{
		GetCaptureLimit() += 10;
	}

	if(Input::IsKeyTriggered(GLFW_KEY_F5))
	{
		UnLoad();
		StateManager_.ChangeStage();
	}
}

void Level::ShutDown()
{
	UnLoad();
}
