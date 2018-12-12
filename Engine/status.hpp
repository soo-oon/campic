#pragma once
#include "Component.hpp"

enum class Life_Type
{
	Dead, Live
};

class Status : public Component
{

public:
	Status(int Object_hp , int object_damage, float object_speed);
	bool Initialize(Object* Ob);
	void Update(float dt);
	void Delete();

	bool GetLived(){return isLived;}
	void SetSpeed(float speed){ move_speed = speed; }
	float GetSpeed(){	return move_speed;}
	int GetDamage() { return damage; }
	void Damaged_hp(int damage_level);
private:
	int hp;
	int damage;
	float move_speed;
	bool isLived = true;
};
