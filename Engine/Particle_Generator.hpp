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
	Particle_Generator(int rate_ = 50, float lifeTime_ = 1.0f, float sizeVariance_ = 5, vector2 startVelocity_ = { 0,0 },
		vector2 randomVelocity_ = {1,1}, vector2 emitSize_ = {0,0})
		: emitRate(rate_), lifeTime_Control(lifeTime_), sizeVariance_Control(sizeVariance_), startVelocity(startVelocity_), randomVelocity(randomVelocity_), emitSize(emitSize_)
	{
		for(int i = 0; i<emitRate; ++i)
		{
		    Particle temp{ lifeTime_Control, sizeVariance_Control, startVelocity };
		    particles.push_back(std::make_unique<Particle>(temp));
		}
	}

	bool Initialize(Object* Ob) override;
	void Update(float dt) override;
	void Delete() override;
	std::vector<std::unique_ptr<Particle>>& GetParticles() { return particles; }

	/*void SetEmitRate(float rate);
	void SetStartVelocity(vector2 velocity);
	void SetRadomVelocity(vector2 velocity);
	void SetEmitSize(vector2 size);
	void ChangeSprite(const std::string path);
	void SetLifeTime(float lifeTime_);
	void SetSizeVariance(float sizeVariance_);*/

private:
	//void SetDirection();
	//vector2 GetRandomVelocity();

	//Direction direction_ = Direction::None;
        int emitRate;
	float lifeTime_Control;
	float sizeVariance_Control;
	vector2 startVelocity;
	vector2 randomVelocity;
	vector2 emitSize;

	std::vector<std::unique_ptr<Particle>> particles;
};