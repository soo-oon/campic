#include "Level3.hpp"

void Level3::Initialize()
{

}

void Level3::Update(float dt)
{
	if (Input::IsKeyTriggered(GLFW_KEY_0))
		BackToMenu();
}

void Level3::ShutDown()
{
	UnLoad();
}
