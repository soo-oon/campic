#pragma once
#include "System.hpp"
#include "Objectmanager.hpp"

class Sound : public System
{
public: 
	void GetStateForSoundObject(Objectmanager* obj);
};