/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Sound.hpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Kang Tae Wook
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

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
#include <map>

class Sound : public System
{
public:
    bool Initialize() override;
    void Update(float dt) override;
    void Quit() override;

	FMOD::System*& GetFMODSystem() { return system; }
	std::map<std::string,FMOD::Sound*>& GetSoundMap() { return sound_map; }

	bool Play(std::string filePath);
	bool Pause(std::string filePath);
	bool Stop(std::string filePath);
	bool SetLoop(std::string filePath, int loop_count);
	bool SetVolume(float volume);
	bool SetMute(bool mute);
	bool IsPlaying();
	void AddSound(const std::string& filePath);
	//bool CreateStream(const std::string & filePath);
	bool IsChannelValid();
	int GetSoundMode();
	void SetSoundSpeed(std::string filePath, float speed);
	void LoadSounds();

private:
	int fmod_result = FMOD_OK;
	int loop = FMOD_LOOP_OFF;
	FMOD::System* system = nullptr;
	FMOD::Sound* sound = nullptr;
	FMOD::Channel* channel = nullptr;

	std::map<std::string,FMOD::Sound*> sound_map;

	class SOUND
	{};

};
