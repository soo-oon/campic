#include "Sound.hpp"
#include "fmod.hpp"
#include <cassert>
#include "Input.hpp"
#include <iostream>

bool Sound::Initialize()
{
	if (System_Create(&system) != FMOD_OK)
	{
		assert(false);
		return false;
	}

	// Check FMOD version
	unsigned int version;
	fmod_result = system->getVersion(&version);
	if (fmod_result != FMOD_OK)
	{
		assert(false);
		return false;
	}

	// Make sure there is a sound card devices on the machine
	int driverCount = 0;
	fmod_result = system->getNumDrivers(&driverCount);

	if (fmod_result != FMOD_OK)
	{
		assert(false);
		return false;
	}

	// Initialize our Instance with 36 Channels
	fmod_result = system->init(32, FMOD_INIT_NORMAL, nullptr);
	{
		if(fmod_result != FMOD_OK)
		{
			assert(false);
			return false;
		}
	}

    return true;
}

void Sound::Update(float dt)
{
	fmod_result = system->update();
	if(fmod_result != FMOD_OK)
		assert(false);

	if (Input::IsKeyTriggered(GLFW_KEY_5))
	{
		if (IsPlaying())
			Stop();
		else
			Play();
	}
}

void Sound::Quit()
{
	system->close();
	system->release();
}

bool Sound::Play()
{
	if (IsChannelValid())
	{
		//check if sound is playing
		bool isPlaying = false;
		fmod_result = channel->isPlaying(&isPlaying);
		if (fmod_result != FMOD_OK)
		{
			assert(false);
			return false;
		}

		// if its already playing, just continue
		if (isPlaying)
			return true;
	}

	// Start playing the sound
	fmod_result = system->playSound(sound, nullptr, false, &channel);
	if (fmod_result != FMOD_OK)
	{
		assert(false);
		return false;
	}

	return true;
}

bool Sound::Pause()
{
	if (!IsChannelValid())
		return true;

	// Get sound paused state
	//bool isPaused = false;
	/*fmod_result = channel->getPaused(&isPaused);
	if (fmod_result != FMOD_OK)
	{
		assert(false);
		return false;
	}*/

	// If it's already paused, don't bother
	/*if (!isPaused)
		return true;*/

	// Pause the sound
	fmod_result = channel->setPaused(true);
	if (fmod_result != FMOD_OK)
	{
		assert(false);
		return false;
	}

	return true;
}

bool Sound::Stop()
{
	if (!IsChannelValid())
		return true;

	if (!IsPlaying())
		return true;

	fmod_result = channel->stop();
	if(fmod_result != FMOD_OK)
	{
		channel = nullptr;
		assert(false);
		return false;
	}

	channel = nullptr;

	return true;
}

bool Sound::SetLoop(bool loop)
{
	loop = loop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;

	if (!sound)
		return false;

	// Infite loops
	if (loop)
	{
		sound->setLoopCount(-1);
	}

	// Set the channel with the new mode
	fmod_result = sound->setMode(GetSoundMode());
	if (fmod_result != FMOD_OK)
	{
		assert(fmod_result);
		return false;
	}
	return true;
}

bool Sound::SetVolume(float volume)
{
	if (!IsChannelValid())
		return false;

	fmod_result = channel->setVolume(volume);
	if (fmod_result != FMOD_OK)
	{
		assert(fmod_result);
		return false;
	}

	return true;
}

bool Sound::SetMute(bool mute)
{
	if (!IsChannelValid())
		return false;

	fmod_result = channel->setMute(mute);
	if (fmod_result != FMOD_OK)
	{
		assert(fmod_result);
		return false;
	}

	return true;
}

bool Sound::IsPlaying()
{
	if (!IsChannelValid())
		return false;

	bool isPlaying = false;
	fmod_result = channel->isPlaying(&isPlaying);
	if (fmod_result != FMOD_OK)
	{
		assert(fmod_result);
		return false;
	}

	return isPlaying;
}

bool Sound::CreateSound(const std::string& filePath)
{
	// Create sound
	fmod_result = system->createSound(filePath.c_str(), GetSoundMode(), nullptr, &sound);
	if (fmod_result != FMOD_OK)
	{
		assert(false);
		return false;
	}
	return true;
}

bool Sound::CreateStream(const std::string& filePath)
{
	// Create sound
	fmod_result = system->createStream(filePath.c_str(), GetSoundMode(), nullptr, &sound);
	if (fmod_result != FMOD_OK)
	{
		assert(false);
		return false;
	}

	return true;
}

bool Sound::IsChannelValid()
{
	if (!channel)
		return false;

	// Do a query and see if it fails or not
	bool value;
	return channel->isPlaying(&value) == FMOD_OK;
}

int Sound::GetSoundMode()
{
	return FMOD_3D | loop;
}