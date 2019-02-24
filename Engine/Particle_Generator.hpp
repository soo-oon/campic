/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Particle.hpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

#pragma once
#include "Component.hpp"
#include "vector2.hpp"
#include "Particle.hpp"
#include <vector>


class Particle_Generator : public Component
{
public:
	Particle_Generator(int rate_ = 50, float lifeTime_ = 5.0f, float sizeVariance_ = 3.0f, float color_duration_ = 10.0f
		, vector2 startVelocity_ = { 0,0 }, vector2 randomVelocity_ = { 1,1 }, 
		vector2 particle_size_ = { 10.0f, 10.0f }, vector2 emitSize_ = { 0,0 }, std::string path = {})
		: emitRate(rate_), lifeTime_Control(lifeTime_), sizeVariance_Control(sizeVariance_), 
			color_duration(color_duration_), startVelocity(startVelocity_), 
				randomVelocity(randomVelocity_), emitSize(emitSize_), particle_size(particle_size_)
	{
		for(int i = 0; i<emitRate; ++i)
		{
		    Particle temp{ lifeTime_Control, sizeVariance_Control, color_duration, 
		    	startVelocity, randomVelocity, particle_size, path };
		    particles.push_back(std::make_unique<Particle>(temp));
		}
	}

	bool Initialize(Object* Ob) override;
	void Update(float dt) override;
	void Delete() override;
	std::vector<std::unique_ptr<Particle>>& GetParticles() { return particles; }

	bool IsActive() { return isActive; }
	void ToggleActive() { isActive = !isActive; }

	void SetEmitRate(int rate);
	void SetStartVelocity(vector2 velocity);
	void SetRandomVelocity(vector2 velocity);
	void ChangeSprite(const std::string path);
	void SetLifeTime(float lifeTime_);
	void SetSizeVariance(float sizeVariance_);
	//void SetEmitSize(vector2 size);

	int GetEmitRate() { return emitRate; }
	float GetLifeTimeControl() { return lifeTime_Control; }
	float GetSizeVarianceControl() { return sizeVariance_Control; }
	float GetColorDuration() { return color_duration; }
	vector2 GetStartVelocity() { return startVelocity; }
	vector2 GetRandomVelocity() { return randomVelocity; }
	vector2 GetEmitSize() { return emitSize; }
	std::string GetPath() { return path; }

private:
    int emitRate;
	float lifeTime_Control;
	float sizeVariance_Control;
	float color_duration;
	vector2 startVelocity;
	vector2 randomVelocity;
	vector2 particle_size;
	vector2 emitSize;
	bool isActive = true;

	std::string path;

	std::vector<std::unique_ptr<Particle>> particles;
};