#pragma once
#include <string>
#include "Component.hpp"


class UI : public Component
{
public:
	UI(std::string id_);

	bool Initialize(Object* Ob) override;
	void Update(float dt) override;
	void Delete() override;

	std::string GetId() const { return id; }

private:
	std::string id;
};

