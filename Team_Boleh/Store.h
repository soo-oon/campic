#pragma once
#include "State.hpp"

class Store : public State
{
public:
    Store()
    {
        information_ = State_Information::Game;
    }
    void Initialize() override;
    void Update(float dt) override;
    void ShutDown() override;

private:
    Object *room1;
};
