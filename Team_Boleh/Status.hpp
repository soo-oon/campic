#pragma once
#include "Component.hpp"

enum class ObjectType
{
	Player, Sword, Enemy, Boss, Wall, Door, Item, Shooting, None
};

class Status : public Component
{
public:
	Status(ObjectType object_type_ = ObjectType::None, int hp_ = 5, int attack_damage_ = 1, float speed_ = 1.0f, bool is_alive_ = true)
		: object_type(object_type_), hp(hp_), attack_damage(attack_damage_), speed(speed_), is_alive(is_alive_)
	{}

	bool Initialize(Object* Ob) override;
	void Update(float dt) override;
	void Delete() override;

	ObjectType GetObjectType() { return object_type; }
	bool IsAlive() { return is_alive; }
	void SetSpeed(float speed_) { speed = speed_; }
	float GetSpeed() { return speed; }
	int GetDamage() { return attack_damage; }
	void Damaged(int damage);
	int GetHp() { return hp; }

private:
	ObjectType object_type;
	int hp;
	int attack_damage;
	float speed;
	bool is_alive = true;

};