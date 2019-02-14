#include "Particle.hpp"
#include <iostream>

bool Particle::Initialize(vector2 position, vector2 random_velocity)
{
	particle_obj->SetTranslation(position);
        SetDirection(random_velocity);
	return true;
}

void Particle::Update(float dt, vector2 random_velocity)
{
	lifeTime -= dt;

	if(lifeTime > 0.0f)
	{
            UpdateDirection(random_velocity, dt);
	    particle_obj->GetMesh().Change_Alpha_Value(dt * 100);

            if(particle_obj->GetMesh().GetColor(0).Alpha <= 0)
            {
                particle_obj->GetMesh().ChangeColor({ 255,255,255 });
            }
	}
	else
	{
		isrespawn = true;
	}
}

void Particle::RespawnParticleObj(Object* obj)
{
    particle_obj->SetTranslation(obj->GetTransform().GetTranslation());
    particle_obj->GetMesh().ChangeColor({ 255,255,255 });
    isrespawn = false;
    lifeTime = static_lifeTime;
}

void Particle::SetDirection(vector2 random_velocity)
{
    int random;

    if(random_velocity.x == 0)
    {
        random = rand() % 2;

        switch (random)
        {
        case 0:
            direction_ = Direction::N;
            break;
        case 1:
            direction_ = Direction::S;
            break;
        default:
            break;
        }
    }
    else if(random_velocity.y == 0)
    {
        random = rand() % 2;

        switch (random)
        {
        case 0:
            direction_ = Direction::E;
            break;
        case 1:
            direction_ = Direction::W;
            break;
        default:
            break;
        }
    }
    else
    {
        random = rand() % 8;

        switch (random)
        {
        case 0:
            direction_ = Direction::N;
            break;
        case 1:
            direction_ = Direction::S;
            break;
        case 2:
            direction_ = Direction::E;
            break;
        case 3:
            direction_ = Direction::W;
            break;
        case 4:
            direction_ = Direction::NE;
            break;
        case 5:
            direction_ = Direction::NW;
            break;
        case 6:
            direction_ = Direction::SE;
            break;
        case 7:
            direction_ = Direction::SW;
            break;
        default:
            break;
        }
    }
}

void Particle::UpdateDirection(vector2 random_velocity, float dt)
{
    auto temp = particle_obj->GetTransform().GetTranslation();
    float temp_velocity_x = rand() % static_cast<int>(random_velocity.x);
    float temp_velocity_y = rand() % static_cast<int>(random_velocity.y);

    switch (direction_)
    {
    case Direction::N:
        particle_obj->SetTranslation({ temp.x + (startVelocity.x ) + (temp_velocity_x)
            , temp.y + (startVelocity.y) + (temp_velocity_y) });
        break;
    case Direction::S:
        particle_obj->SetTranslation({ temp.x + (startVelocity.x ) + (temp_velocity_x)
            , temp.y + (startVelocity.y) - (temp_velocity_y) });
        break;
    case Direction::E:
        particle_obj->SetTranslation({ temp.x + (startVelocity.x) + (temp_velocity_x)
            , temp.y + (startVelocity.y) + (temp_velocity_y) });
        break;
    case Direction::W:
        particle_obj->SetTranslation({ temp.x + (startVelocity.x ) - (temp_velocity_x)
            , temp.y + (startVelocity.y) + (temp_velocity_y) });
        break;
    case Direction::NE:
        particle_obj->SetTranslation({ temp.x + (startVelocity.x ) + (temp_velocity_x)
            , temp.y + (startVelocity.y) + (temp_velocity_y) });
        break;
    case Direction::NW:
        particle_obj->SetTranslation({ temp.x + (startVelocity.x ) - (temp_velocity_x)
            , temp.y + (startVelocity.y) + (temp_velocity_y) });
        break;
    case Direction::SE:
        particle_obj->SetTranslation({ temp.x + (startVelocity.x ) + (temp_velocity_x)
            , temp.y + (startVelocity.y) - (temp_velocity_y) });
        break;
    case Direction::SW:
        particle_obj->SetTranslation({ temp.x + (startVelocity.x ) - (temp_velocity_x)
            , temp.y + (startVelocity.y) - (temp_velocity_y) });
        break;
    default:
        break;
    /*case Direction::N:
        particle_obj->SetTranslation({ temp.x + (startVelocity.x * dt) + (temp_velocity_x)*dt
            , temp.y+ (startVelocity.y*dt) + (temp_velocity_y)*dt});
        break;
    case Direction::S:
        particle_obj->SetTranslation({ temp.x + (startVelocity.x * dt) + (temp_velocity_x)*dt
            , temp.y + (startVelocity.y*dt) - (temp_velocity_y)*dt });
        break;
    case Direction::E:
        particle_obj->SetTranslation({ temp.x + (startVelocity.x * dt) + (temp_velocity_x)*dt
            , temp.y + (startVelocity.y*dt) + (temp_velocity_y)*dt });
        break;
    case Direction::W:
        particle_obj->SetTranslation({ temp.x + (startVelocity.x * dt) - (temp_velocity_x)*dt
            , temp.y + (startVelocity.y*dt) + (temp_velocity_y)*dt });
        break;
    case Direction::NE:
        particle_obj->SetTranslation({ temp.x + (startVelocity.x * dt) + (temp_velocity_x)*dt
            , temp.y + (startVelocity.y*dt) + (temp_velocity_y)*dt });
        break;
    case Direction::NW:
        particle_obj->SetTranslation({ temp.x + (startVelocity.x * dt) - (temp_velocity_x)*dt
            , temp.y + (startVelocity.y*dt) + (temp_velocity_y)*dt });
        break;
    case Direction::SE:
        particle_obj->SetTranslation({ temp.x + (startVelocity.x * dt) + (temp_velocity_x)*dt
            , temp.y + (startVelocity.y*dt) - (temp_velocity_y)*dt });
        break;
    case Direction::SW:
        particle_obj->SetTranslation({ temp.x + (startVelocity.x * dt) - (temp_velocity_x)*dt
            , temp.y + (startVelocity.y*dt) - (temp_velocity_y)*dt });
        break;
    default:
        break;*/
    }
}