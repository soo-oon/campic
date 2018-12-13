#pragma once
#include "System.hpp"
#include <memory>
#include "Object.hpp"

class IndependentObj : public System
{
public:
	IndependentObj()
		: player(std::make_unique<Object>()), sword(std::make_unique<Object>())
	{}

	bool Initialize() override;
	void Update(float dt) override;
	void Quit() override;

private:
	std::unique_ptr<Object> player;
	std::unique_ptr<Object> sword;
};
