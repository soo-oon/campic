#include "PhysicsComponent.hpp"



void Physics::CollisionOn()
{
	collision_switch = true;
}
void Physics::SetMass(float mass)
{
	inverse_mass = 1.f / mass;
}
void Physics::AddForce(glm::vec2 force )
{
	force_accumlator += force;
}
void Physics::SetVelocity(glm::vec2 velocity)
{
	this->velocity = velocity;
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