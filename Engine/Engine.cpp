#include "Engine.hpp"
#include "Application.hpp"
#include "StateManager.hpp"
#include "Graphics.hpp"
#include <iostream>
#include "Input.hpp"
#include "State.hpp"
#include "Sound.hpp"
#include "Physics.hpp"
#include "Imgui_System.hpp"
#include "JSON.hpp"
#include "HUD_System.hpp"

namespace
{
	Application* Application_ = nullptr;
	Graphics* Graphic_ = nullptr;
	Objectmanager* Objectmanager_ = nullptr;
	State* State_ = nullptr;
	Sound* Sound_ = nullptr;
	Physics* Physics_ = nullptr;
	Imgui_System* Imgui = nullptr;
	JSON* Json = nullptr;
	HUD* HUD_ = nullptr;
	State* hud_state = nullptr;
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
	AddSystem(new HUD());
	AddSystem(new Imgui_System());
	AddSystem(new JSON());

	Application_ = GetSystemByTemplate<Application>();
	Graphic_ = GetSystemByTemplate<Graphics>();
	Physics_ = GetSystemByTemplate<Physics>();
	Sound_ = GetSystemByTemplate<Sound>();
	HUD_ = GetSystemByTemplate<HUD>();
	Imgui = GetSystemByTemplate<Imgui_System>();
	Json = GetSystemByTemplate<JSON>();

	for (auto i : systems)
	{
		i->Initialize();
	}

	hud_state = HUD_->GetHUDlevel();
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
		Graphic_->HUD_Draw(hud_state->GetObjectManager());

		Graphic_->EndDraw();

		Application_->SetDispalyAreaSize(Graphic_, State_);

		Sound_->GetFMODSystem();

		Imgui->SetFMOD(Sound_);
		Imgui->SetObjectManger(Objectmanager_);
		Imgui->Draw();

		Json->UpdateLevel(GetSystemByTemplate<StateManager>());


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
