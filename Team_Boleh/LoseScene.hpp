/* Start Header ---------------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name : LoseScene.hpp
Language  : C++
Platform  : Visual Studio 2017
Project   : CamPic
Primary   : TaeWook Kang
Secondary :
- End Header ----------------------------------------------------------------*/
#pragma once
#include "State.hpp"
#include "Button.hpp"

class LoseScene : public State
{
public:
    LoseScene() 
    {
        information_ = State_Information::CutScene;
    }

    void Initialize() override;
    void Update(float dt) override;
    void ShutDown() override;
    void TakePrevLevel();
private:
	Object* background = nullptr;
    Object* m_game_over = nullptr;
    Object* m_restart = nullptr;
    Object* m_menu = nullptr;
    Object* mouse_icon = nullptr;

    float timer = 0.f;
    bool is_end_start_sprite = false;
    bool is_start_animation = false;

	bool change = false;

    std::string m_this_level;

};

