#pragma once

enum ComponentType
{
	clear,
	sprite,
};

class Component
{
private:

public:
	virtual ~Component() {};
	ComponentType type = clear;

	virtual bool Initialize() = 0;
	virtual void Update(float dt) = 0;
	virtual void Delete() = 0;
};