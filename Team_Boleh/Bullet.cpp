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
		auto player_ = StateManager_.GetCurrentState()->GetPlayerObjectPointer();
		if (player_ != nullptr)
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

			auto b_collision_t = base_obj->GetComponentByTemplate<Collision>()->GetCollisionTransform().GetScale() / 2;
			auto m_collision_t = m_object->GetComponentByTemplate<Collision>()->GetCollisionTransform().GetScale()/2;

			if (normalize(player_->GetTransform().GetTranslation() - m_object->GetTransform().GetTranslation()).x >= 0)
			{
				m_object->SetTranslation({ m_object->GetTransform().GetTranslation().x + b_collision_t.x + m_collision_t.x +1, 
					m_object->GetTransform().GetTranslation().y});
				m_object->GetComponentByTemplate<Collision>()->ChangeCollisionBoxTranslation({ m_object->GetTransform().GetTranslation() });
			}
			else
			{
				m_object->SetTranslation({ m_object->GetTransform().GetTranslation().x - b_collision_t.x - m_collision_t.x -1, 
					m_object->GetTransform().GetTranslation().y });
				m_object->GetComponentByTemplate<Collision>()->ChangeCollisionBoxTranslation({ m_object->GetTransform().GetTranslation() });
			}
		}

	}
	else
	{
		auto player_ = StateManager_.GetCurrentState()->GetPlayerObjectPointer();
		if (player_ != nullptr)
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

			auto b_collision_t = base_obj->GetComponentByTemplate<Collision>()->GetCollisionTransform().GetScale() / 2;
			auto m_collision_t = m_object->GetComponentByTemplate<Collision>()->GetCollisionTransform().GetScale() / 2;

			if (normalize(player_->GetTransform().GetTranslation() - m_object->GetTransform().GetTranslation()).x >= 0)
			{
				m_object->SetTranslation({ m_object->GetTransform().GetTranslation().x + b_collision_t.x + m_collision_t.x + 1,
					m_object->GetTransform().GetTranslation().y });
				m_object->GetComponentByTemplate<Collision>()->ChangeCollisionBoxTranslation({ m_object->GetTransform().GetTranslation() });
			}
			else
			{
				m_object->SetTranslation({ m_object->GetTransform().GetTranslation().x - b_collision_t.x - m_collision_t.x - 1,
					m_object->GetTransform().GetTranslation().y });
				m_object->GetComponentByTemplate<Collision>()->ChangeCollisionBoxTranslation({ m_object->GetTransform().GetTranslation() });
			}
		}
	}
}
