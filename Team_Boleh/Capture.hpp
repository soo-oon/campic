#pragma once
#include "Component.hpp"
#include <vector>

class Capture : public Component
{
public:
	bool Initialize(Object* Ob) override;
	void Update(float dt) override;
	void Delete() override;

	std::vector<Object*>& GetCaptureObject() { return capture_object; }
private:
	void Capturing();
	std::vector<Object*> capture_object;
};
