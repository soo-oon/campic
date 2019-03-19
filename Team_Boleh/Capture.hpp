#pragma once
#include "Component.hpp"
#include <vector>
#include <memory>

class Capture : public Component
{
public:
	bool Initialize(Object* Ob) override;
	void Update(float dt) override;
	void Delete() override;

	std::vector<std::shared_ptr<Object>>& GetCaptureObject() { return capture_object; }
private:
	void Capturing();
	std::vector<std::shared_ptr<Object>> capture_object;
};
