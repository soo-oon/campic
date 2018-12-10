#pragma once
#include "Component.hpp"

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
private:
	int hp;
	int damage;
	float move_speed;
	bool isLived = true;
};
