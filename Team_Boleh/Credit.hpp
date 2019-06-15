#pragma once
#include "State.hpp"
#include "MenuPage.hpp"

class Credit : public State
{
public:
	Credit()
	{
		information_ = State_Information::Credit;
	}

	void Initialize() override;
	void Update(float dt) override;
	void ShutDown() override;

private:
	vector2 screen_size = Application_.GetScreenSize();
	Object* m_credit1 = nullptr;
	Object* m_credit2 = nullptr;
	Object* m_credit3 = nullptr;
	Object* mouse_icon = nullptr;
        Object* button = nullptr;

	bool page1 = true;
	bool page2 = false;
	bool page3 = false;

	float timer = 0.f;
};

