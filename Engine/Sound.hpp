#pragma once
#include "System.hpp"
#include <fmod.hpp>


class Sound : public System
{
public:
    FMOD::System* s_system;
    FMOD::Sound* s_sound;
    FMOD::Channel* s_channel;

    bool Initialize() override;
    void Update(float dt) override;
    void Quit() override;
};
