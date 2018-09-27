#include "Engine.hpp"
#include "Application.hpp"
#include "StateManager.hpp"
#include <iostream>
#include "Input.hpp"

bool Engine::Initialize()
{
    AddSystem(new Application());
    AddSystem(new StateManager());
    AddSystem(new Objectmanager());

    for (auto i : systems)
        i->Initialize();

    gameTimer.Reset();

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
