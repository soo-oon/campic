#include "Sound.hpp"

bool Sound::Initialize(Object * Ob)
{
	object = Ob;

	return true;
}

void Sound::Update(float /*dt*/)
{
}

void Sound::Delete()
{
}

void Sound::Play(std::string path)
{
	AudioManager_.PlaySFX(audio_source + path, volume);
}

void Sound::AddSound(std::string path_)
{
	paths.push_back(audio_source + path_);
	AudioManager_.LoadSFX(path_);
}

