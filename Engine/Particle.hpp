#pragma once

#include "Object.hpp"
#include "Sprite.hpp"


enum class Direction
{
	N, S, E, W, NE, NW, SE, SW, None
};

class Particle
{
public:
	Particle(float lifeTime_ = 1.0f, float sizeVariance_ = 5.0f, vector2 velocity_ = { 0,0 })
		: lifeTime(lifeTime_), sizeVariance(sizeVariance_), startVelocity(velocity_)
	{
		particle_obj = new Object();
		particle_obj->SetMesh(mesh::CreateBox(1, { 255,255,255 }));
		particle_obj->SetScale(50.0f);
		particle_obj->AddComponent(new Sprite());

		static_lifeTime = lifeTime;

		for(auto component : particle_obj->GetComponent())
		{
			component->Initialize(particle_obj);
		}
	}

	bool Initialize(vector2 position, vector2 random_velocity);
	void Update(float dt, vector2 random_velocity);

	bool IsRespawn() { return isrespawn; }
	Object* GetParticleObject() { return particle_obj; }
	void RespawnParticleObj(Object* obj);

        void SetDirection(vector2 random_velocity);
	//void SetTranslation(vector2 position);
	//void SetSize(vector2 size);

private:
	void UpdateDirection(vector2 random_velocity, float dt);
	float lifeTime;
	float sizeVariance;
	vector2 startVelocity;
	float static_lifeTime;
	Object* particle_obj = nullptr;
	bool isrespawn = false;

        Direction direction_ = Direction::None;
};
