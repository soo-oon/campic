#include "Application.hpp"
#include "Engine.hpp"

int main()
{
    Engine engine;

    engine.Initialize();
    
    engine.Update();
  
    engine.ShutDown();

    return 0;
}
