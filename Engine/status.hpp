#pragma once
#include "Component.hpp"
#include "Object.hpp"

enum class Life_Type
{
	Dead, Live
};

class Status : public Component
{

public:
	Status(int Object_hp = 5, int object_damage = 1, float object_speed = 1.0f);
	bool Initialize(Object* Ob);
	void Update(float dt);
	void Delete();

	bool GetLived(){return isLived;}
	void SetSpeed(float speed){ move_speed = speed; }
	float GetSpeed(){	return move_speed;}
	int GetDamage() { return damage; }
	void Damaged_hp(int damage_level);
	int GetHp() { return hp; }

private:
	int hp;
	int damage;
	float move_speed;
	bool isLived = true;
};
