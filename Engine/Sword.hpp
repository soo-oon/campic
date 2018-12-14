/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Sword.hpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary : Jung Soon Woo
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/
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
