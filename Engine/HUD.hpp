/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: HUD.hpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/
#pragma once
#include "State.hpp"
#include "Object.hpp"
#include <memory>

class HUD
{
public:
	bool Initialize(State* HUD_State = nullptr);
	void Update(float dt);
	void Quit();

	std::vector<std::shared_ptr<Object>>& Get_HUD_Object_Manager() { return HUD_Object_Manager; }
	void Add_HUD_Object(Object* obj);


	void Toggle_HUD_Active() { isHUDActive = !isHUDActive; }

private:
	void SetPlayer(Object* obj);
	void HUD_Activing_Search();

	bool isHUDActive = false;
	State* m_HUD_State = nullptr;

	std::vector<std::shared_ptr<Object>> HUD_Object_Manager;

};

extern HUD HUD_;