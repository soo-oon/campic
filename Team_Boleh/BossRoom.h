#pragma once
#include "State.hpp"

class BossRoom : public State
{
public:
    BossRoom()
    {
        information_ = State_Information::Game;
    }
    void Initialize() override;
    void Update(float dt) override;
    void ShutDown() override;
};

