#include <iostream>
#include "Bullet.hpp"
#include "State.hpp"

void Bullet::Initialize(Object* Ob)
{
	if (base_obj == nullptr)
		base_obj = Ob;

	if(m_type == Projectile_Type::Cannon)
	{
		if(m_parent != nullptr)
		{
			std::cout << "Should Change the m_type To Fire!" << std::endl;
		}
	}

	MakeBullet();
}

void Bullet::Update(float dt)
{
	if(m_parent == nullptr)
	{
		//m_parent = StateManager_.GetCurrentState()->GetPlayerObjectPointer();
	}

	m_lifetime -= dt;

	if(m_lifetime <= 0.0f)
	{
		m_object->SetObjectDead();
	}
}

void Bullet::Delete()
{
}

bool Bullet::IsDead()
{
	return m_object->IsDead();
}

void Bullet::MakeBullet()
{
	if(m_type == Projectile_Type::Cannon)
	{
		m_object = new Object();
		m_object->SetTranslation(base_obj->GetTransform().GetTranslation());
		m_object->SetScale({ 70, 70 });
		m_object->SetDepth(0.2f);
		m_object->SetMesh(mesh::CreateBox());
		m_object->AddInitComponent(new Sprite("asset/images/cannon_bullet.png"));
		m_object->AddInitComponent(new RigidBody());
		m_object->AddInitComponent(new Collision(box_));
		m_object->SetObjectType(ObjectType::Projectile);

	}
	else
	{
		m_object = new Object();
		m_object->SetTranslation(m_parent->GetTransform().GetTranslation());
		m_object->SetScale({ 30, 30 });
		m_object->SetDepth(0.2f);
		m_object->SetMesh(mesh::CreateBox());
		m_object->AddInitComponent(new Sprite("asset/images/cannon_bullet.png"));
		m_object->AddInitComponent(new RigidBody());
		m_object->AddInitComponent(new Collision(box_));
		m_object->SetObjectType(ObjectType::Projectile);
	}
}
