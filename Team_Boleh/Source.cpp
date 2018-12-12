#include "Application.hpp"
#include "Engine.hpp"
#include "example_level.hpp"
#include "StateManager.hpp"
#include "statemanager_test.hpp"
#include "MapEditorTest.hpp"
#include "Particle_level.hpp"

int main()
{
    Engine* engine = new Engine();

    engine->Initialize();

	engine->GetSystemByTemplate<StateManager>()->AddStage("example",new example());
	engine->GetSystemByTemplate<StateManager>()->AddStage("test", new test_statemanager());
	engine->GetSystemByTemplate<StateManager>()->AddStage("MapEditorTest", new MapEditorTest());
	engine->GetSystemByTemplate<StateManager>()->AddStage("Particle", new Particle_level());

    engine->Update();
  
    engine->ShutDown();

    return 0;
}
