#pragma once
#include "Object.hpp"

enum class Projectile_Type
{
	Cannon,
	Weapon,
};

class Bullet
{
public:
	Bullet(float lifetime = 3.0f, Projectile_Type type = Projectile_Type::Cannon, Object* parent = nullptr)
		: m_lifetime(lifetime), m_type(type), m_parent(parent)
	{}

	void Initialize(Object* Ob);
	void Update(float dt);
	void Delete();

	bool IsDead();

	Object* GetBullet() { return m_object; }

private:
	void MakeBullet();

	float m_lifetime;
	Projectile_Type m_type;

	Object* m_object = nullptr;
	Object* base_obj = nullptr;
	Object* m_parent = nullptr;
};