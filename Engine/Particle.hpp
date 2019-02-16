#pragma once

#include "Object.hpp"
#include "Sprite.hpp"


class Particle
{
public:
	Particle(float lifeTime_ = 5.0f, float sizeVariance_ = 3.0f, float color_duration_ = 10.0f,
		vector2 start_velocity_ = { 0,0 }, vector2 random_velocity_ = {0,0}, std::string path = {})
		: static_lifeTime(lifeTime_), static_sizeVariance(sizeVariance_),
		startVelocity(start_velocity_), static_color_duration(color_duration_), static_random_velocity(random_velocity_)
	{
		lifeTime = static_lifeTime;
		sizeVariance = static_sizeVariance;
		color_duration = static_color_duration;
		random_velocity = static_random_velocity;

		particle_obj = new Object();
		particle_obj->SetMesh(mesh::CreateBox(1, { 255,255,255 }));
		particle_obj->SetScale(50.0f);

		if (path.empty())
		{
			particle_obj->AddComponent(new Sprite());
		}
		else
		{
			particle_obj->AddComponent(new Sprite(path));
			
		}

		for(auto component : particle_obj->GetComponent())
		{
			component->Initialize(particle_obj);
		}
	}

	bool Initialize(vector2 position);
	void Update(float dt, vector2 random_velocity_);

	bool IsRespawn() { return isrespawn; }
	void RespawnParticleObj(Object* obj);
	Object* GetParticleObject() { return particle_obj; }

	void SetOriginScale(vector2 size) { origin_size = size; }
	void SetStartVelocity(vector2 velocity) { startVelocity = velocity; }
	void SetRandomVelocity(vector2 velocity) { static_random_velocity = velocity; }
	void SetSizeVariance(float sizeVariance_) { static_sizeVariance = sizeVariance_; }
	void ChangeSprite(const std::string path) { particle_obj->GetComponentByTemplate<Sprite>()->ChangeSprite(path); }
	void SetLifeTime(float lifeTime_) { static_lifeTime = lifeTime_; }
	//void SetEmitSize(vector2 size)

	float GetLifeTime() { return static_lifeTime; }
	float GetSizeVariance() { return static_sizeVariance; }
	float GetColorDuration() { return static_color_duration; }
	vector2 GetRandomVelocity() { return static_random_velocity; }

private:
	void UpdateDirection(float dt);
	float lifeTime;
	float sizeVariance;
	float color_duration;
	vector2 startVelocity;
	vector2 random_velocity{};
	Object* particle_obj = nullptr;
	bool isrespawn = false;

//static
private:
	float static_lifeTime;
	float static_sizeVariance;
	float static_color_duration;
	vector2 static_random_velocity{};
	vector2 origin_size{};

	//Direction direction_ = Direction::None;
};
