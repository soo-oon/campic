#include "Enemy.hpp"

Enemy::Enemy(MoveType move_type)
{
	move_t = move_type;
}

bool Enemy::Initialize(Object * Ob)
{
	object = Ob;
	return false;
}

void Enemy::Update(float dt)
{
}

void Enemy::Delete()
{
}

void Enemy::MoveEnemy(MoveType move_type)
{
}
