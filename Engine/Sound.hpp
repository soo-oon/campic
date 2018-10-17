#pragma once
#include "System.hpp"
#include <fmod.hpp>
#include "fmod_common.h"
#include <fmod_errors.h>


class Sound : public System
{
public:
    FMOD::System* s_system;
    FMOD::Sound* s_sound;
    FMOD::Channel* s_channel;

	bool Initialize() override;
    void Update(float dt) override;
    void Quit() override;

	void createSound(Sound *pSound, const char* pFile);

	void playSound(Sound pSound, bool bLoop);

};
