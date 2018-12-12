#pragma once

#include "Component.hpp"

enum class MoveType
{
	straight,
};

class Enemy : public Component
{
public:
	Enemy(MoveType move_type);
	bool Initialize(Object* Ob);
	void Update(float dt);
	void Delete();
	void MoveEnemy(MoveType move_type);
private:
	MoveType move_t;
};
