#include "Level.hpp"
#include "Input.hpp"
#include "UI.hpp"

void Level::Initialize()
{
}

void Level::Update(float dt)
{
	if (Input::IsKeyTriggered(GLFW_KEY_0))
		BackToMenu();
}

void Level::ShutDown()
{
	UnLoad();
}
