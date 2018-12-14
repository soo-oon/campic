/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Enemy.cpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Jung Soon Woo
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/


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
