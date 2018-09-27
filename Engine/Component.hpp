#pragma once

class Component
{
public:
	virtual ~Component() {};
	virtual bool Initialize() = 0;
	virtual void Update(float dt) = 0;
	virtual void Delete() = 0;
};