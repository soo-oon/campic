#include "Particle.hpp"
#include "RandomFunction.hpp"
#include <iostream>

bool Particle::Initialize(vector2 position)
{
	particle_obj->SetTranslation(position);
	
	float temp_x_dir = RandomNumberGenerator(-static_random_velocity.x, static_random_velocity.x);
	float temp_y_dir = RandomNumberGenerator(-static_random_velocity.y, static_random_velocity.y);

	random_velocity.x = temp_x_dir;
	random_velocity.y = temp_y_dir;

	float temp_color_duration = RandomNumberGenerator(0.0f, static_color_duration);
	color_duration = temp_color_duration;

	float temp_life_time = RandomNumberGenerator(0.0f, static_lifeTime);
	lifeTime = temp_life_time;

	float temp_size = RandomNumberGenerator(1.0f, static_sizeVariance);
	sizeVariance = temp_size;
	particle_obj->SetScale(origin_size * sizeVariance);

	return true;
}

void Particle::Update(float dt, vector2 random_velocity_)
{
	lifeTime -= dt;

	if(lifeTime > 0.0f)
	{
		UpdateDirection(dt);

	    if(!particle_obj->GetMesh().GetColor(0).isAlphaDone)
	    {
			particle_obj->GetMesh().Decrease_Alpha(color_duration * dt);
	    }
		else
		{
			particle_obj->GetMesh().Increase_Alpha(color_duration * dt);
		}
	}
	else
	{
		isrespawn = true;
	}
}

void Particle::RespawnParticleObj(Object* obj)
{
	Initialize(obj->GetTransform().GetTranslation());
    particle_obj->GetMesh().ChangeColor({ 255,255,255 });
    isrespawn = false;
    lifeTime = static_lifeTime;
}


void Particle::UpdateDirection(float dt)
{
	vector2 temp_position = particle_obj->GetTransform().GetTranslation();

	particle_obj->SetTranslation({ temp_position.x + random_velocity.x + startVelocity.x,
		temp_position.y + random_velocity.y + startVelocity.y});
}