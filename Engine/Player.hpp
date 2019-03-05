/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Player.hpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

#pragma once
#include "Component.hpp"
#include <vector>
#include "Object.hpp"

struct vector2;

class Player : public Component
{
public:
	bool Initialize(Object* Ob);
	void Update(float dt);
	void Delete();
	void MovePlayer();
	void SetCardList(std::string card);
	void ClearCardList();
	std::vector<std::string> GetCardList();
	//void PlayerMove(vector2 mouse_position);

private:
	void PlayerAnimation(float angle);

	vector2 direction;
    int boost = 1;
	std::vector<std::string> card_list = {};
};
