/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Component.hpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/


#pragma once


class Object;

class Component
{
private:
public:
	/*Component()
		:object(nullptr)
	{};*/
    virtual ~Component()
    {};
    Object* object;

    virtual bool Initialize(Object* Ob) = 0;
    virtual void Update(float dt) = 0;
    virtual void Delete() = 0;
};
