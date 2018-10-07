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
vector2 Physics::GetPosition()
{
	return position;
}
bool Physics::Initialize(Object* Ob)
{
	force_accumlator = { 0,0 };
	velocity = { 0,0 };
	position = Ob->GetTransform().GetTranslation();
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
