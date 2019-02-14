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

enum class Component_Type
{
	None, 
	Sprite,
	RigidBody,
	Camera,
	Animation,
	Collision,
	Particle
};

class Object;

class Component
{
private:
public:
    virtual ~Component()
    {};
	Component_Type type = Component_Type::None;
    Object* object;

    virtual bool Initialize(Object* Ob) = 0;
    virtual void Update(float dt) = 0;
    virtual void Delete() = 0;
};
