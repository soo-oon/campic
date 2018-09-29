#include "Application.hpp"
#include "Engine.hpp"
#include "example_level.hpp"
#include "StateManager.hpp"

int main()
{
    Engine* engine = new Engine();

    engine->Initialize();

	static auto check_ = new example();

    dynamic_cast<StateManager*>(engine->GetSystem(SystemList::statemanager))->AddStage(check_);

    engine->Update();
  
    engine->ShutDown();

    return 0;
}
