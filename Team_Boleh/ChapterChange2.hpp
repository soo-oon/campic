/* Start Header ---------------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name : ChapterChange2.hpp
Language  : C++
Platform  : Visual Studio 2017
Project   : CamPic
Primary   : TaeWook Kang
Secondary :
- End Header ----------------------------------------------------------------*/
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

