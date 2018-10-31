#include "Engine.hpp"
#include "Application.hpp"
#include "StateManager.hpp"
#include "Graphics.hpp"
#include <iostream>
#include "Input.hpp"
#include "State.hpp"
#include "Sound.hpp"

namespace
{
	Application* App = nullptr;
	Graphics* Graphic = nullptr;
	Objectmanager* Obj = nullptr;
	State* Current_State = nullptr;
	Imgui_Setup* Imgui = nullptr;
}

bool Engine::IsQuit;

bool Engine::Initialize()
{
    systems.clear();
    AddSystem(new Application());
    AddSystem(new StateManager());
    AddSystem(new Graphics());
    AddSystem(new Sound());
	AddSystem(new Imgui_Setup());

	App = GetSystemByTemplate<Application>();
	Graphic = GetSystemByTemplate<Graphics>();
	Imgui = GetSystemByTemplate<Imgui_Setup>();

	for (auto i : systems)
	{
		if (systems.at(4))
			Imgui->SetWindow(App->GetWindow());
		i->Initialize();
	}

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

		Current_State = GetSystemByTemplate<StateManager>()->GetCurrentState();
		Obj = Current_State->GetObjectManager();
		Imgui->SetObjectManger(Obj);


        Graphic->Draw(Obj);
		Imgui->Draw();
		Graphic->EndDraw();
		App->SetDispalyAreaSize(Graphic, Current_State);


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
