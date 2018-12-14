/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Engine.hpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

#pragma once
#include <vector>
#include "System.hpp"
#include "Timer.hpp"
#include "Objectmanager.hpp"

enum SystemList
{
    appication,
    statemanager,
    graphics
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
