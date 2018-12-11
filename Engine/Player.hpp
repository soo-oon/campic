#pragma once
#include "Component.hpp"

class Player : public Component
{
public:
	bool Initialize(Object* Ob);
	void Update(float dt);
	void Delete();
	void MovePlayer();
private:
};
