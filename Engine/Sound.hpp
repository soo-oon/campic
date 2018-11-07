#pragma once
#include "System.hpp"
#include <fmod.hpp>
#include <fmod_errors.h>
#include <fmod.h>
#include <fmod_codec.h>
#include <fmod_uwp.h>
#include <fmod_dsp_effects.h>
#include <fmod_common.h>
#include <fmod.hpp>
#include <string>

class Sound : public System
{
public:
    FMOD::System* system;
    FMOD::Sound* sound;
    FMOD::Channel* channel;

    bool Initialize() override;
    void Update(float dt) override;
    void Quit() override;

	bool Play();
	bool Pause();
	bool Stop();
	bool SetLoop(bool loop);
	bool SetVolume(float volume);
	bool SetMute(bool mute);
	bool IsPlaying();
	bool CreateSound(const std::string& filePath);
	bool CreateStream(const std::string & filePath);
	bool IsChannelValid();
	int GetSoundMode();

private:
	int fmod_result = FMOD_OK;
	int loop = FMOD_LOOP_OFF;
};
