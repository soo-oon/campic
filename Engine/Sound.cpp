#include "Sound.hpp"
#include "fmod.hpp"

bool Sound::Initialize()
{
	if (FMOD::System_Create(&s_system) != FMOD_OK)
	{
		// Report Error
		return;
	}

	int driverCount = 0;
	s_system->getNumDrivers(&driverCount);

	if (driverCount == 0)
	{
		// Report Error
		return;
	}

	// Initialize our Instance with 36 Channels
	s_system->init(36, FMOD_INIT_NORMAL, 0);

	return true;
}

void Sound::Update(float /*dt*/)
{

}

void Sound::Quit()
{

}

void Sound::createSound(Sound * pSound, const char * pFile)
{
	//s_system->createSound(pFile, FMOD_HARDWARE, 0, pSound);
}

void Sound::playSound(Sound pSound, bool bLoop = false)
{
	if (!bLoop)
		s_sound->setMode(FMOD_LOOP_OFF);
	else
	{
		s_sound->setMode(FMOD_LOOP_NORMAL);
		s_sound->setLoopCount(-1);
	}

	//s_system->playSound(FMOD_CHANNEL_FREE, pSound, false, 0);
}