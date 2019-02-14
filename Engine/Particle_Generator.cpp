/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Particel.cpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

#include "Particle_Generator.hpp"

bool Particle_Generator::Initialize(Object* Ob)
{
	object = Ob;

	for(auto& particle : particles)
	{
		particle->Initialize(object->GetTransform().GetTranslation(), randomVelocity);
	}
	return true; 
}

void Particle_Generator::Update(float dt)
{
	for(auto& particle_obj : particles)
	{
		particle_obj->Update(dt, randomVelocity);
		if(particle_obj->IsRespawn())
		{
			particle_obj->RespawnParticleObj(object);
		}
	}
}

void Particle_Generator::Delete()
{
}

//void Particle_Generator::SetDirection()
//{
//	if(randomVelocity.y ==0)
//	{
//		int random = rand() % 2;
//
//		switch (random)
//		{
//		case 0:
//			direction_ = Direction::E;
//			break;
//		case 1:
//			direction_ = Direction::W;
//			break;
//		default:
//			break;
//		}
//	}
//	else if(randomVelocity.x == 0)
//	{
//		int random = rand() % 2;
//
//		switch (random)
//		{
//		case 0:
//			direction_ = Direction::N;
//			break;
//		case 1:
//			direction_ = Direction::S;
//			break;
//		default:
//			break;
//		}
//	}
//	else
//	{
//		int random = rand() % 8;
//
//		switch (random)
//		{
//		case 0:
//			direction_ = Direction::N;
//			break;
//		case 1:
//			direction_ = Direction::S;
//			break;
//		case 2:
//			direction_ = Direction::E;
//			break;
//		case 3:
//			direction_ = Direction::W;
//			break;
//		case 4:
//			direction_ = Direction::NE;
//			break;
//		case 5:
//			direction_ = Direction::NW;
//			break;
//		case 6:
//			direction_ = Direction::SE;
//			break;
//		case 7:
//			direction_ = Direction::SW;
//			break;
//		default:
//			break;
//		}
//	}
//}

//vector2 Particle_Generator::GetRandomVelocity()
//{
//
//}

