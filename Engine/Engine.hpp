#pragma once
#include <vector>
#include "System.hpp"
#include "Timer.hpp"
#include "Objectmanager.hpp"

enum SystemList
{
    appication,
    statemanager,
    graphics,
	imgui
};

class Engine
{
public:
    bool Initialize();
    void Update();
    void Quit();
    void ShutDown();

    System* GetSystem(unsigned ID) { return systems[ID]; }
    void AddSystem(System* new_system);
    static bool IsQuit;

    template <typename SYSTEM>
    SYSTEM* GetSystemByTemplate() const;

private:
    Timer gameTimer{};
    float dt = 0;
    std::vector<System*> systems;
};

template <typename SYSTEM>
SYSTEM* Engine::GetSystemByTemplate() const
{
    for (auto i : systems)
    {
        if (typeid(SYSTEM) == typeid(*i))
        {
            return dynamic_cast<SYSTEM*>(i);
        }
    }
    return nullptr;
}
