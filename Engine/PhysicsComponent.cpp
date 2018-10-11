#include "PhysicsComponent.hpp"


void Physics::CollisionOn()
{
    collision_switch = true;
}

void Physics::SetMass(float mass)
{
    inverse_mass = 1.f / mass;
}

void Physics::AddForce(vector2 force)
{
    force_accumlator += force;
}

void Physics::SetVelocity(vector2 velocity)
{
    this->velocity = velocity;
}

vector2 Physics::GetVelocity()
{
    return velocity;
}

vector2 Physics::GetPosition()
{
    return position;
}


bool Physics::Initialize(Object* Ob)
{
	object = Ob;
    force_accumlator = {0, 0};
    velocity = {0, 0};
	object = Ob;
    return true;
}

void Physics::Update(float dt)
{
	gravity = 1 / object->GetGravity();
    // calculate current velocity.
    velocity += inverse_mass * (force_accumlator * dt);

    // zero out accumulated force
    force_accumlator = {0, 0};

    //friction always activated
    velocity *= friction;

    // integrate position
    if (magnitude(velocity) < 0.001f)
	    velocity = 0;
	
    // integrate position
	object->GetTransform().SetTranslation({ (object->GetTransform().GetTranslation().x + (velocity * dt).x), (object->GetTransform().GetTranslation().y + (velocity * dt).y) });
}

void Physics::Delete()
{
}
