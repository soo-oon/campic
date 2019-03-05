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
#include <iostream>

bool Particle_Generator::Initialize(Object* Ob)
{
	if (object == nullptr)
	{
		object = Ob;
	}

	for(auto& particle : particles)
	{
		particle->Initialize(object);
	}
	return true; 
}

void Particle_Generator::Update(float dt)
{
	inter_time += dt;
	if (isActive)
	{
		for (auto& particle_obj : particles)
		{
			if (is_repeat)
			{
				particle_obj->Update(dt, randomVelocity);
				if (particle_obj->IsRespawn())
				{
					particle_obj->RespawnParticleObj(object);
				}
			}
			else
			{
				if(duration_time > inter_time)
				{
					particle_obj->Update(dt, randomVelocity);
					if (particle_obj->IsRespawn())
					{
						particle_obj->RespawnParticleObj(object);
					}
				}
				else
				{
					isActive = false;
					inter_time = 0.0f;
				}
			}

		}
	}
}

void Particle_Generator::Delete()
{
}

void Particle_Generator::SetEmitRate(int rate)
{
	particles.clear();

	for(int i = 0; i<rate; ++i)
	{
		Particle temp{ lifeTime_Control, sizeVariance_Control, color_duration, 
			startVelocity, randomVelocity, particle_size };
		particles.push_back(std::make_unique<Particle>(temp));
	}

	Initialize(object);
}

void Particle_Generator::SetStartVelocity(vector2 velocity)
{
	for (auto& particle_obj : particles)
	{
		particle_obj->SetStartVelocity(velocity);
	}
}

void Particle_Generator::SetRandomVelocity(vector2 velocity)
{
	for (auto& particle_obj : particles)
	{
		particle_obj->SetRandomVelocity(velocity);
	}
}


void Particle_Generator::ChangeSprite(const std::string path)
{
	for (auto& particle_obj : particles)
	{
		particle_obj->ChangeSprite(path);
	}
}

void Particle_Generator::SetLifeTime(float lifeTime_)
{
	for (auto& particle_obj : particles)
	{
		particle_obj->SetLifeTime(lifeTime_);
	}
}

void Particle_Generator::SetSizeVariance(float sizeVariance_)
{
	for (auto& particle_obj : particles)
	{
		particle_obj->SetSizeVariance(sizeVariance_);
	}
}

void Particle_Generator::SetEmitSize(vector2 size)
{
	for(auto& particle_obj : particles)
	{
		particle_obj->SetEmitSize(size);
	}
}

void Particle_Generator::SetParticle_Fire_Type(Particle_Fire_Type type_)
{
	for (auto& particle_obj : particles)
	{
		particle_obj->SetParticle_Fire_Type(type_);
	}
}

//void Particle_Generator::SetEmitSize(vector2 size)
//{
//	for (auto& particle_obj : particles)
//	{
//	}
//}
