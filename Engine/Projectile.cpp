#include "Projectile.hpp"
#include "Object.hpp"
#include "Input.hpp"

bool Projectile::Initialize(Object * Ob)
{
    object = Ob;
    return true;
}

void Projectile::Update(float dt)
{
    while (m_shot_count == 0)
    {
        if (Projectile_Type::Arrow == m_projectile)
            ArrowUpdate();
        else
            CannonUpdate();
        --m_shot_count;
    }
}

void Projectile::Delete()
{
}

void Projectile::CannonUpdate()
{
        std::shared_ptr<Object> missile = std::make_shared<Object>();
        missile->SetTranslation({ object->GetTransform().GetTranslation() });
        missile->SetScale({ 50.0f, 50.0f });
        missile->SetMesh(mesh::CreateBox(1, { 255,255,255, 255 }));
        missile->SetDepth(0.0f);
        missile->AddComponent(new RigidBody());
        missile->AddComponent(new Collision(box_));
        missile->SetObjectType(ObjectType::Item_Dynamic);
        missile->GetComponentByTemplate<RigidBody>()->SetVelocity({ 50,50 });
        Objectmanager_.AddObject(missile.get());
}

void Projectile::ArrowUpdate()
{
    std::shared_ptr<Object> arrow = std::make_shared<Object>();
    arrow->SetTranslation({ object->GetTransform().GetTranslation() });
    arrow->SetScale({ 50.0f, 50.0f });
    arrow->SetMesh(mesh::CreateBox(1, { 255,255,255, 255 }));
    arrow->SetDepth(0.0f);
    arrow->AddComponent(new RigidBody());
    arrow->AddComponent(new Collision(box_));
    arrow->SetObjectType(ObjectType::Item_Dynamic);
    arrow->GetComponentByTemplate<RigidBody>()->SetVelocity({ 0,-50 });
    Objectmanager_.AddObject(arrow.get());
}
