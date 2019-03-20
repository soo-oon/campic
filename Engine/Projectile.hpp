#pragma once
#include "Component.hpp"

enum class Projectile_Type
{
    Cannon,
    Arrow,
};

class Projectile : public Component
{
public:
    bool Initialize(Object* Ob) override;
    void Update(float dt) override;
    void Delete() override;

public:
    void SetProjectileType(Projectile_Type p_type) { m_projectile = p_type; }

public:
    Projectile_Type GetProjectileType() { return m_projectile; }

    void CannonUpdate();

private:
    Projectile_Type m_projectile;

};

