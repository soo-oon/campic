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
	void SetName(std::string sword_string);
	std::string GetName();
	void Wheelwind();

private:
	float angle = 0;
	bool skill = false;
	std::string sword_name = "trash";
	Object* owner;
};
