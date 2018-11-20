#include "Application.hpp"
#include "Engine.hpp"
#include "example_level.hpp"
#include "StateManager.hpp"
#include "statemanager_test.hpp"
#include "MapEditorTest.hpp"

int main()
{
    Engine* engine = new Engine();

    engine->Initialize();

	engine->GetSystemByTemplate<StateManager>()->AddStage("example",new example());
	engine->GetSystemByTemplate<StateManager>()->AddStage("test", new test_statemanager());
	engine->GetSystemByTemplate<StateManager>()->AddStage("MapEditorTest", new MapEditorTest());

    engine->Update();
  
    engine->ShutDown();

    return 0;
}
