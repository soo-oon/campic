#include "statemanager_test.hpp"
#include "Input.hpp"

void test_statemanager::Initialize()
{
	Load();
}

void test_statemanager::Update(float /*dt*/)
{
	if (Input::IsKeyTriggered(GLFW_KEY_1))
		ChangeLevel("example");
}

void test_statemanager::ShutDown()
{
	UnLoad();
}
