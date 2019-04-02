#pragma once
#include "Component.hpp"
#include <vector>
#include "vector2.hpp"

class Capture : public Component
{
public:
	Capture(vector2 pos) : reset_pos(pos){}

	bool Initialize(Object* Ob) override;
	void Update(float dt) override;
	void Delete() override;

	void SetResetPosition(vector2 size) { reset_pos = size; }
	vector2 GetResetPosition()const { return reset_pos; }

	bool IsCheese() { return cheese; }
	void SetCheese(bool condition) { cheese = condition; }

private:
	void Capturing();
	void CreateCaptureObject();

	bool cheese = false;
	vector2 reset_pos;
	std::vector<Object*> capture_object;
};
