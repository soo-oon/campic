#pragma once
#include "Component.hpp"
#include <memory>

enum class Projectile_Type
{
    Cannon,
    Arrow,
};

class Projectile : public Component
{
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
    int m_shot_count;

};

