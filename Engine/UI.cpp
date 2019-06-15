/* Start Header ---------------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name : UI.cpp
Language  : C++
Platform  : Visual Studio 2017
Project   : CamPic
Primary   : TaeWook Kang
Secondary :
- End Header ----------------------------------------------------------------*/
#include "UI.hpp"

UI::UI(std::string id_,bool IsLock_) : id(id_), IsLock(IsLock_)
{
}


bool UI::Initialize(Object * Ob)
{
	if(object == nullptr)
	{
		object = Ob;
	}
	return true;
}

void UI::Update(float dt)
{
}

void UI::Delete()
{
}