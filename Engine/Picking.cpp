#include "Picking.h"
#include "Input.hpp"

Picking Picking_;

void Picking::Initialize()
{
}

void Picking::Update(float dt)
{

    if(Input::IsMousePressed(GLFW_MOUSE_BUTTON_LEFT))
    {
        for (auto obj = Objectmanager_.GetObjectMap().begin(); obj != Objectmanager_.GetObjectMap().end(); ++obj)
        {
            if (Input::GetMousePos(1.f).x < obj->get()->GetTransform().GetTranslation().x + obj->get()->GetTransform().GetScale().x &&
                Input::GetMousePos(1.f).x > obj->get()->GetTransform().GetTranslation().x - obj->get()->GetTransform().GetScale().x &&
                Input::GetMousePos(1.f).y < obj->get()->GetTransform().GetTranslation().y + obj->get()->GetTransform().GetScale().y &&
                Input::GetMousePos(1.f).y > obj->get()->GetTransform().GetTranslation().y - obj->get()->GetTransform().GetScale().y
                )
                ActiveObject = obj->get();
        }
    }
    else
    {
        ActiveObject = nullptr;
    }

    if(ActiveObject)
        ActiveObject->SetTranslation(Input::GetMousePos(1.f));

}

void Picking::Quit()
{
}
