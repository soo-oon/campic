#pragma once
#include "Component.hpp"
#include <vector>
#include <memory>
#include "Bullet.hpp"

//class Bullet;

class Projectile : public Component
{
public:
	Projectile(float firetime = 5.0f, float lifetime = 3.0f, Projectile_Type type = Projectile_Type::Cannon)
	: m_firetime(firetime), m_lifetime(lifetime), m_type(type)
	{};

	bool Initialize(Object* Ob) override;
	void Update(float dt) override;
	void Delete() override;

	void SetFireDir(vector2 dir) { fire_dir = dir; }
	vector2 GetFireDir() { return fire_dir; }

private:
	void SpawnProjectile();
	void SetProjectileDirection(RigidBody* rigidbody);
	void SetFilpAnimation();
	void CannonUpdate(float dt);
	void WeaponUpdate(float dt);

	//int check = 0;

private:
	std::vector<std::shared_ptr<Bullet>> projectile;

	float m_firetime;
	float m_lifetime;
	Projectile_Type m_type;
	Object* m_parent = nullptr;

	vector2 fire_dir{};

	float m_dt = 0.0f;

/*
public:
    Projectile(Projectile_Type type) : m_projectile(type){}
    bool Initialize(Object* Ob) override;
    void Update(float dt) override;
    void Delete() override;

public:
    void SetProjectileType(Projectile_Type p_type) { m_projectile = p_type; }
    void SetShotCount(int count) { m_shot_count = count; }

public:
    Projectile_Type GetProjectileType() { return m_projectile; }
    int GetShotCount() { return m_shot_count; }

    void CannonUpdate();
    void ArrowUpdate();

private:
    Projectile_Type m_projectile;
    Object* missile;
    Object* arrow;
    int m_shot_count = 3;
*/

};

