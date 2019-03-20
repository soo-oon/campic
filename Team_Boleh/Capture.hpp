#pragma once
#include "Component.hpp"
#include <vector>
#include "vector2.hpp"

class Capture : public Component
{
public:
	Capture(vector2 pos)
		:reset_pos(pos)
	{}

	bool Initialize(Object* Ob) override;
	void Update(float dt) override;
	void Delete() override;

	std::vector<Object*>& GetCaptureObject() { return capture_object; }
private:
	void Capturing();
	void CreateCaptureObject();

	bool cheese = false;
	vector2 reset_pos;
	std::vector<Object*> capture_object;
};
