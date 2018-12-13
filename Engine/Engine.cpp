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
#if _DEBUG
	Imgui_System* Imgui = nullptr;
#endif
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
#if _DEBUG
	AddSystem(new Imgui_System());
#endif
	AddSystem(new JSON());

	Application_ = GetSystemByTemplate<Application>();
	Graphic_ = GetSystemByTemplate<Graphics>();
	Physics_ = GetSystemByTemplate<Physics>();
	Sound_ = GetSystemByTemplate<Sound>();
	HUD_ = GetSystemByTemplate<HUD>();
#if _DEBUG
	Imgui = GetSystemByTemplate<Imgui_System>();
#endif
	Json = GetSystemByTemplate<JSON>();

	for (auto i : systems)
	{
		i->Initialize();
	}

	hud_state = HUD_->GetHUDlevel();
    gameTimer.Reset();
    IsQuit = false;
	srand(static_cast<unsigned int>(time(NULL)));
    return true;
}

void Engine::Update()
{
    while (!IsQuit)
    {
        dt = (float)gameTimer.GetElapsedSeconds();
        gameTimer.Reset();

		State_ = GetSystemByTemplate<StateManager>()->GetCurrentState();
		Objectmanager_ = State_->GetObjectManager().get();

        for (auto i : systems)
        {
            i->Update(dt);
        }
		
		Physics_->PhysicsObjectUpdate(Objectmanager_);


		HUD_->SetObjectManager(Objectmanager_);
		Graphic_->HUD_Draw(Objectmanager_, hud_state->GetObjectManager().get());
		Graphic_->Draw(Objectmanager_);

		Graphic_->EndDraw();

		Application_->SetDispalyAreaSize(Graphic_, State_);

		Sound_->GetSoundMap();
#if _DEBUG
		Imgui->SetSoundManager(Sound_);
		Imgui->SetObjectManger(Objectmanager_);
		Imgui->Draw();
#endif

		//Json->UpdateLevel(GetSystemByTemplate<StateManager>());
		Json->UpdateState(GetSystemByTemplate<StateManager>());
        if (Input::IsKeyTriggered(GLFW_KEY_ESCAPE))
            IsQuit = true;
    }

    Quit();
}

void Engine::Quit()
{
	Json->SaveAtEnd();
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
