#include "Engine.hpp"
#include "Application.hpp"
#include "StateManager.hpp"
#include "Graphics.hpp"
#include <iostream>
#include "Input.hpp"
#include "test.hpp"

bool Engine::IsQuit;
bool Engine::Initialize()
{
	systems.clear();
    AddSystem(new Application());
    AddSystem(new StateManager());
    AddSystem(new Objectmanager());
	AddSystem(new Graphics());

    for (auto i : systems)
        i->Initialize();

    gameTimer.Reset();
	IsQuit = false;
    return true;
}

void Engine::Update()
{
    while (!IsQuit)
    {
        dt = (float)gameTimer.GetElapsedSeconds();
        gameTimer.Reset();

        for (auto i : systems)
            i->Update(dt);
		
		dynamic_cast<Graphics*>(systems.at(graphics))->Draw(*check);
		dynamic_cast<Graphics*>(systems.at(graphics))->EndDraw();

		dynamic_cast<Application*>(systems.at(appication))->SetDispalyAreaSize(dynamic_cast<Graphics*>(systems.at(graphics)));

        if (Input::IsKeyTriggered(GLFW_KEY_ESCAPE))
            IsQuit = true;

        if (Input::IsKeyTriggered(GLFW_KEY_G))
            std::cout << "hi" << std::endl;
    }

    Quit();
}

void Engine::Quit()
{
    for (auto i : systems)
        i->Quit();
}

void Engine::ShutDown()
{
    systems.clear();
}

void Engine::AddSystem(System * new_system)
{
    systems.push_back(new_system);
}
