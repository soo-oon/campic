/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Enemy.hpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Jung Soon Woo
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

#pragma once

#include "Component.hpp"
#include "Object.hpp"
#include "time.h"

enum class MoveType
{
	straight,
        angler
};

enum class HadCard
{
    red,
    blue,
    green,
    black,
};

class Enemy : public Component
{
public:
	Enemy(MoveType move_type);
	bool Initialize(Object* Ob);
	void Update(float dt);
	void Delete();
	void MoveEnemy();
        void StraightMove();
        void AnglerMove();

        void CardDrop();
private:
	MoveType move_t;
};
