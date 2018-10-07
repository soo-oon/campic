#include "PhysicsComponent.hpp"



void Physics::CollisionOn()
{
	collision_switch = true;
}
void Physics::SetMass(float mass)
{
	inverse_mass = 1.f / mass;
}
void Physics::AddForce(vector2 force )
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
bool Physics::Initialize()
{
	force_accumlator = { 0,0 };
	velocity = { 0,0 };
	return true;
}
void Physics::Update(float dt)
{
	// calculate current velocity.
	velocity += inverse_mass * (force_accumlator * dt);
	
	// zero out accumulated force
	force_accumlator = { 0,0 };

	// integrate position
	position += velocity * dt;
}

void Physics::Delete()
{
}
