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
#include <vector>
#include <vector2.hpp>
#include "Mesh.hpp"
#include "Sprite.hpp"
#include "Transform.hpp"

class Sprite;

struct Particle_Obj
{
	Particle_Obj(Transform transfrom, Mesh mesh, vector2 velocity, float life_time, std::string path_);
	Transform transform_;
	Mesh mesh_;
	vector2 velocity_;
	float life_time_;
	Sprite* sprite_ = nullptr;

};

class Particle : public Component
{
public:
	Particle(int amount, float life_time, int particle_number, vector2 offset)
		: amount_(amount), const_life_time(life_time), update_particle_number(particle_number), offset_(offset)
	{}

	bool Particle_Generate(Transform transform, Mesh mesh, vector2 velocity, std::string path_);
	bool Initialize(Object* Ob)override;
	void Update(float dt) override;
	void Delete() override;
	auto& GetParticle_Objets() { return particle_objs; }

	int UnusedParticle();
	void RespawnParticle(Particle_Obj* particle_obj, vector2 offset);
	int last_used_particle_index = 0;

private:
	int amount_;
	float const_life_time;
	int update_particle_number;
	vector2 offset_;
	std::vector<std::unique_ptr<Particle_Obj>> particle_objs;
};
