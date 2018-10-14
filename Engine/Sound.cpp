#include "Sound.hpp"
#include "fmod.hpp"

bool Sound::Initialize()
{
    FMOD::System_Create(&s_system);

    s_system->init(1, FMOD_INIT_NORMAL, 0);

    return true;
}

void Sound::Update(float /*dt*/)
{
}

void Sound::Quit()
{
}
