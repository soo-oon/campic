#include "Engine.hpp"
#include "Application.hpp"
#include "StateManager.hpp"
#include "Graphics.hpp"
#include <iostream>
#include "Input.hpp"
#include "Stage.hpp"
#include "Sound.hpp"

bool Engine::IsQuit;

bool Engine::Initialize()
{
    systems.clear();
    AddSystem(new Application());
    AddSystem(new StateManager());
    AddSystem(new Graphics());
    AddSystem(new Sound());

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

        State* state = GetSystemByTemplate<StateManager>()->GetCurrentState();

		
        GetSystemByTemplate<Graphics>()->Draw(state->GetObjectManager());
        GetSystemByTemplate<Graphics>()->EndDraw();
        GetSystemByTemplate<Application>()->SetDispalyAreaSize(GetSystemByTemplate<Graphics>(), state);
		GetSystemByTemplate<Application>()->GetObjectManager(state->GetObjectManager());

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

void Engine::AddSystem(System* new_system)
{
    systems.push_back(new_system);
}
