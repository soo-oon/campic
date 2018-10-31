#include "Engine.hpp"
#include "Application.hpp"
#include "StateManager.hpp"
#include "Graphics.hpp"
#include <iostream>
#include "Input.hpp"
#include "State.hpp"
#include "Sound.hpp"
#include "Physics.hpp"

namespace
{
	Application* Application_ = nullptr;
	Graphics* Graphic_ = nullptr;
	Objectmanager* Objectmanager_ = nullptr;
	State* State_ = nullptr;
	Physics* Physics_ = nullptr;
	Imgui_Setup* Imgui = nullptr;
}

bool Engine::IsQuit;

bool Engine::Initialize()
{
    systems.clear();
    AddSystem(new Application());
    AddSystem(new StateManager());
    AddSystem(new Graphics());
	AddSystem(new Physics());
    AddSystem(new Sound());
	AddSystem(new Imgui_Setup());

	Application_ = GetSystemByTemplate<Application>();
	Graphic_ = GetSystemByTemplate<Graphics>();
	Physics_ = GetSystemByTemplate<Physics>();
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

		State_ = GetSystemByTemplate<StateManager>()->GetCurrentState();
		Objectmanager_ = State_->GetObjectManager();

		Physics_->PhysicsObjectUpdate(Objectmanager_);

		Graphic_->Draw(Objectmanager_);
		Graphic_->EndDraw();

		Application_->SetDispalyAreaSize(Graphic_, State_);
		Application_->GetObjectManager(Objectmanager_);

		Imgui->SetObjectManger(Obj);
		Imgui->Draw();

        if (Input::IsKeyTriggered(GLFW_KEY_ESCAPE))
            IsQuit = true;
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
