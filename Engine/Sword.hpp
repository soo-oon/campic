#pragma once
#include "Component.hpp"
#include "Object.hpp"
#include <vector2.hpp>

struct vector2;

class Sword : public Component
{
public:
	Sword(Object* player);

	bool Initialize(Object* Ob);
	void Update(float dt);
	void SetOwner(Object* player);
	void Delete() override;
	void SwordMove(vector2 mouse_position);
private:
	Object* owner;
};
