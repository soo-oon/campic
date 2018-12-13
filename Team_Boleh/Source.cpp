#include "Application.hpp"
#include "Engine.hpp"
#include "example_level.hpp"
#include "StateManager.hpp"
#include "statemanager_test.hpp"
#include "MapEditorTest.hpp"
#include "Particle_level.hpp"
#include "StartMenu.hpp"
#include "SplashScreen.hpp"
#include "Demonstrate.hpp"

int main()
{
    Engine* engine = new Engine();

    engine->Initialize();

	engine->GetSystemByTemplate<StateManager>()->AddStage("Splash_Screen", new SplashScreen());
	engine->GetSystemByTemplate<StateManager>()->AddStage("StartMenu", new StartMenu());
	engine->GetSystemByTemplate<StateManager>()->AddStage("example",new example());
	engine->GetSystemByTemplate<StateManager>()->AddStage("test", new test_statemanager());
	engine->GetSystemByTemplate<StateManager>()->AddStage("MapEditorTest", new MapEditorTest());
	engine->GetSystemByTemplate<StateManager>()->AddStage("Particle", new Particle_level());
	engine->GetSystemByTemplate<StateManager>()->AddStage("Startmenu", new StartMenu());
	engine->GetSystemByTemplate<StateManager>()->AddStage("Demonstrate", new Demonstrate());

    engine->Update();
  
    engine->ShutDown();

    return 0;
}
