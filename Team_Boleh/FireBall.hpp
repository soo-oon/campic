#pragma once
#include "Component.hpp"

class Object;

class FireBall : public Component
{
public:
	FireBall(Object* player_, Object* sword, float time_) : o_player(player_), o_sword(sword), life_time(time_)
	{}

	bool Initialize(Object* Ob) override;
	void Update(float dt) override;
	void Delete() override;

	bool IsDead() { return isdead;  }
private:
	Object* o_player = nullptr;
	Object* o_sword = nullptr;
	float account_time = 0;
	float life_time = 0;
	bool isdead = false;

};
