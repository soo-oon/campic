#include "UI.hpp"

UI::UI(std::string id_) : id(id_)
{
}


bool UI::Initialize(Object * Ob)
{
	if(object == nullptr)
	{
		object = Ob;
	}
	return true;
}

void UI::Update(float dt)
{
}

void UI::Delete()
{
}
