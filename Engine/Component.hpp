#pragma once

enum ComponentType
{
	clear,
	sprite,
	physics,
};

class Object;

class Component
{
private:
public:
	virtual ~Component() {};
	ComponentType type = clear;

	virtual bool Initialize(Object* Ob) = 0;
	virtual void Update(float dt) = 0;
	virtual void Delete() = 0;
};