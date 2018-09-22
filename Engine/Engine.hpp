#pragma once
#include <vector>
#include "System.hpp"
#include "Timer.hpp"

class Engine
{
public:
    bool Initialize();
    void Update();
    void Quit();
    void ShutDown();

    void AddSystem(System* new_system);

private:
    bool IsQuit = false;
    Timer gameTimer{};
    float dt = 0;
    std::vector<System*> systems;
};