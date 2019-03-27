#include "Projectile.hpp"
#include "Object.hpp"
#include <iostream>
#include "State.hpp"

/*
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
*/
bool Projectile::Initialize(Object* Ob)
{
	if (object == nullptr)
		object = Ob;

	if(m_type == Projectile_Type::Weapon)
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

	if(m_type == Projectile_Type::Cannon)
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
	switch(m_type)
	{
	case Projectile_Type::Cannon:
		{
			auto player_ = StateManager_.GetCurrentState()->GetPlayerObjectPointer();

			if(normalize(player_->GetTransform().GetTranslation() - object->GetTransform().GetTranslation()).x >= 0)
			{
				rigidbody->SetVelocity({ 100, 150 });

			}
			else
			{
				rigidbody->SetVelocity({ -100, 150 });
			}
		}
		break;

	case Projectile_Type::Weapon:
		{
			auto player_ = StateManager_.GetCurrentState()->GetPlayerObjectPointer();

			if(!player_->GetComponentByTemplate<Animation>()->IsFiip())
			{
				rigidbody->SetVelocity({ 1000, 0 });
			}
			else
			{
				rigidbody->SetVelocity({ -1000, 0 });
			}
		}
		break;

	default:
		break;
	}
}

void Projectile::SetFilpAnimation()
{
	auto player_ = StateManager_.GetCurrentState()->GetPlayerObjectPointer();

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
	vector2 player_pos = StateManager_.GetCurrentState()->GetPlayerObjectPointer()->GetTransform().GetTranslation();

	if(object->GetTransform().GetParent() == nullptr)
	{
		if(Input::IsKeyTriggered(GLFW_KEY_SPACE))
		{
			object->SetTranslation(player_pos);
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
