#pragma once
#include "State.hpp"
#include "Button.hpp"

class ChapterChange2 : public State
{
public:
    ChapterChange2()
    {
        information_ = State_Information::CutScene;
    }

    void Initialize() override;
    void Update(float dt) override;
    void ShutDown() override;
private:
    Object* start = nullptr;
    Object* mouse_icon = nullptr;
    Object* button = nullptr;

    float timer = 0.f;
};

