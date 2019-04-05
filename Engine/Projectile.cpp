#include "Projectile.hpp"
#include "Object.hpp"
#include <iostream>
#include "State.hpp"

bool Projectile::Initialize(Object* Ob)
{
	if (object == nullptr)
		object = Ob;

	if (m_type == Projectile_Type::Weapon)
	{
		m_dt = m_firetime;
		if (m_parent == nullptr)
		{
			std::cout << "Should Set Parent Object" << std::endl;
		}
	}

	return true;
}

void Projectile::Update(float dt)
{
	m_dt += dt;

	SetFilpAnimation();

	if (m_type == Projectile_Type::Cannon)
	{
		CannonUpdate(dt);
	}
	else
	{
		WeaponUpdate(dt);
	}

}

void Projectile::Delete()
{
}

void Projectile::SpawnProjectile()
{
	switch (m_type)
	{
	case Projectile_Type::Cannon:
	{
		Bullet bullet_c(m_lifetime, Projectile_Type::Cannon, m_parent);
		projectile.push_back(std::make_shared<Bullet>(bullet_c));
		projectile.at(projectile.size() - 1)->Initialize(object);
		Objectmanager_.AddObject(projectile.at(projectile.size() - 1)->GetBullet());
		SetProjectileDirection(projectile.at(projectile.size() - 1)->GetBullet()->GetComponentByTemplate<RigidBody>());
	}
	break;

	case Projectile_Type::Weapon:
	{
		Bullet bullet_a(m_lifetime, Projectile_Type::Weapon, m_parent);
		projectile.push_back(std::make_shared<Bullet>(bullet_a));
		projectile.at(projectile.size() - 1)->Initialize(object);
		Objectmanager_.AddObject(projectile.at(projectile.size() - 1)->GetBullet());
		SetProjectileDirection(projectile.at(projectile.size() - 1)->GetBullet()->GetComponentByTemplate<RigidBody>());
	}
	break;

	default:
		break;
	}

}

void Projectile::SetProjectileDirection(RigidBody* rigidbody)
{
	switch (m_type)
	{
	case Projectile_Type::Cannon:
	{
		auto player_ = StateManager_.GetCurrentState()->GetPlayerObjectPointer();

		if (normalize(player_->GetTransform().GetTranslation() - object->GetTransform().GetTranslation()).x >= 0)
		{
			rigidbody->SetVelocity({ fire_dir });

		}
		else
		{
			rigidbody->SetVelocity({ -fire_dir.x, fire_dir.y });
		}
	}
	break;

	case Projectile_Type::Weapon:
	{
		auto player_ = StateManager_.GetCurrentState()->GetPlayerObjectPointer();

		if (!player_->GetComponentByTemplate<Animation>()->IsFiip())
		{
			rigidbody->SetVelocity({ fire_dir });
		}
		else
		{
			rigidbody->SetVelocity({ -fire_dir.x, fire_dir.y });
		}
	}
	break;

	default:
		break;
	}
}

void Projectile::SetFilpAnimation()
{
	if (auto player_ = StateManager_.GetCurrentState()->GetPlayerObjectPointer();
		player_ != nullptr)
	{

		if (object->GetComponentByTemplate<Animation>() != nullptr)
		{
			if (normalize(player_->GetTransform().GetTranslation() - object->GetTransform().GetTranslation()).x >= 0)
			{
				object->GetComponentByTemplate<Animation>()->SetFlip(false);

			}
			else
			{
				object->GetComponentByTemplate<Animation>()->SetFlip(true);
			}
		}
		else
		{
			if (object->GetTransform().GetParent() != nullptr)
			{
				if (!player_->GetComponentByTemplate<Animation>()->IsFiip())
				{
					object->GetComponentByTemplate<Sprite>()->SetFlip(false);

				}
				else
				{
					object->GetComponentByTemplate<Sprite>()->SetFlip(true);
				}
			}
		}
	}
}

void Projectile::CannonUpdate(float dt)
{
	if (m_dt >= m_firetime)
	{
		object->GetComponentByTemplate<Animation>()->ChangeAnimation("cannon_fire", "cannon_standing");
		SpawnProjectile();
		m_dt = 0.0f;
	}


	for (auto bullet = projectile.begin(); bullet != projectile.end();)
	{
		bullet->get()->Update(dt);

		if (bullet->get()->IsDead())
		{
			bullet = projectile.erase(bullet);
		}
		else
		{
			++bullet;
		}

	}
}

void Projectile::WeaponUpdate(float dt)
{
	if (m_parent == nullptr)
	{
		m_parent = StateManager_.GetCurrentState()->GetPlayerObjectPointer();
	}

	if (object->GetTransform().GetParent() == nullptr)
	{
		if (Input::IsKeyTriggered(GLFW_KEY_SPACE))
		{
			object->SetTranslation(m_parent->GetTransform().GetTranslation());
			object->SetParent(&m_parent->GetTransform());
		}
	}
	else
	{
		if (m_dt >= m_firetime)
		{
			if (Input::IsKeyTriggered(GLFW_KEY_SPACE))
			{
				SpawnProjectile();
				m_dt = 0.0f;
			}
		}
	}

	for (auto bullet = projectile.begin(); bullet != projectile.end();)
	{
		if (bullet->get()->GetParent() == nullptr)
		{
			bullet->get()->SetParent(m_parent);
		}

		bullet->get()->Update(dt);

		if (bullet->get()->IsDead())
		{
			bullet = projectile.erase(bullet);
		}
		else
		{
			++bullet;
		}

	}
}