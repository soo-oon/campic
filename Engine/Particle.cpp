#include "Particle.hpp"
#include <memory>
#include "Sprite.hpp"
#include "Object.hpp"

Particle_Obj::Particle_Obj(Transform transfrom, Mesh mesh, vector2 velocity, float life_time, std::string path_)
	: transform_(transfrom), mesh_(mesh), velocity_(velocity), life_time_(life_time)
{
	sprite_ = new Sprite();
	transform_.SetDepth(0.9f);
	sprite_->Texture_Load(path_);
}


bool Particle::Particle_Generate(Transform transform, Mesh mesh, vector2 velocity, std::string path_)
{
	for(int i = 0; i <amount_; ++i)
	{
		particle_objs.push_back(std::make_unique<Particle_Obj>(transform, mesh, velocity, const_life_time, path_));
	}

	if (particle_objs.empty())
		return  false;

	return true;
}

bool Particle::Initialize(Object* Ob)
{
	object = Ob;

	if (Ob == nullptr)
		return false;

	if (particle_objs.empty())
		return false;

	return true;
}

void Particle::Update(float dt)
{
	for(int i = 0; i < update_particle_number; ++i)
	{
		int unusedParticle = UnusedParticle();
		RespawnParticle(particle_objs[unusedParticle].get(), offset_);
	}

	for(int i = 0; i <amount_; ++i)
	{
		Particle_Obj* p = particle_objs[i].get();
		p->life_time_ -= dt * (rand() % 10);

		if(p->life_time_ > 0.0f)
		{
			vector2 offset_velocity = p->velocity_ * dt;
			vector2 set_new_translation = p->transform_.GetTranslation() - offset_velocity;
			p->transform_.SetTranslation(set_new_translation);

			p->mesh_.Change_Alpha_Value(dt*3.5f);
		}
	}
}

void Particle::Delete()
{

}

int Particle::UnusedParticle()
{
	for(int i = last_used_particle_index; i<amount_; ++i)
	{
		if(particle_objs[i]->life_time_ <= 0.0f)
		{
			last_used_particle_index = i;
			return i;
		}
	}

	for(int i = 0; i<last_used_particle_index; ++i)
	{
		if(particle_objs[i]->life_time_ <= 0.0f)
		{
			last_used_particle_index = i;
			return i;
		}
	}

	last_used_particle_index = 0;
	return 0;
}

void Particle::RespawnParticle(Particle_Obj* particle_obj, vector2 offset)
{
	float random = ((rand() % 1000) - 50) / 10.0f;
	vector2 new_translation = object->GetTransform().GetTranslation() + offset + random;
	particle_obj->transform_.SetTranslation(new_translation);

	Color respawn_color = Color{ 255, 255, 255, 255 };
	particle_obj->mesh_.ChangeColor(respawn_color);

	particle_obj->life_time_ = const_life_time;
	particle_obj->velocity_ = 0.0f;
}
