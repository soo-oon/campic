#include "Projectile.hpp"
#include "Object.hpp"
#include "Input.hpp"

bool Projectile::Initialize(Object * Ob)
{
    object = Ob;
     missile = new Object;
    missile->SetTranslation({ object->GetTransform().GetTranslation() });
    missile->SetScale({ 50.0f, 50.0f });
    missile->SetMesh(mesh::CreateBox(1, { 255,255,255, 255 }));
    missile->SetDepth(0.0f);
    missile->AddComponent(new RigidBody());
    missile->AddComponent(new Collision(box_));
    missile->SetObjectType(ObjectType::Projectile);
    missile->GetComponentByTemplate<RigidBody>()->SetVelocity({ 150,150 });

     arrow = new Object;
    arrow->SetTranslation({ object->GetTransform().GetTranslation() });
    arrow->SetScale({ 50.0f, 50.0f });
    arrow->SetMesh(mesh::CreateBox(1, { 255,255,255, 255 }));
    arrow->SetDepth(0.0f);
    arrow->AddComponent(new RigidBody());
    arrow->AddComponent(new Collision(box_));
    arrow->SetObjectType(ObjectType::Projectile);
    arrow->GetComponentByTemplate<RigidBody>()->SetVelocity({ 0,-50 });

    return true;
}

void Projectile::Update(float dt)
{
    if (Input::IsKeyTriggered(GLFW_KEY_6))
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
    Object* temp = new Object(*missile);
    Objectmanager_.AddObject(temp);
    temp->GetComponentByTemplate<RigidBody>()->SetVelocity({ 150,150 });
}

void Projectile::ArrowUpdate()
{
    Object* temp = new Object(*arrow);
    Objectmanager_.AddObject(temp);
    temp->GetComponentByTemplate<RigidBody>()->SetVelocity({ 0,-150 });
}
