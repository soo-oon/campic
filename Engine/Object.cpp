/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Object.cpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

#include "Object.hpp"
#include "control_angle.hpp"
#include <iostream>

void Object::AddComponent(Component* component)
{
    m_component.push_back(component);
}

void Object::AddInitComponent(Component* component)
{
    component->Initialize(this);
    m_component.push_back(component);
}

void Object::SetMesh(Mesh mesh)
{
    m_mesh = mesh;
}

void Object::SetTranslation(const vector2& position)
{
	m_transform.SetTranslation(position);
}

void Object::SetScale(const vector2& scale)
{
	m_transform.SetScale(scale);

}

void Object::SetRotation(const float& rotation)
{
	m_transform.SetRotation(rotation);
}

void Object::SetDepth(const float& depth)
{
	m_transform.SetDepth(depth);
}

void Object::SetParent(const Transform* transform_)
{
	m_transform.SetParent(transform_);

	auto temp = m_transform.GetWorldToModel();
	affine2d rotate_ = rotation_affine(-m_transform.GetRotation());

	temp *= rotate_;

	m_transform.SetTranslation({ temp.affine[0][2], temp.affine[1][2] });
	m_transform.SetScale({ temp.affine[0][0], temp.affine[1][1] });
}

void Object::SetObjectDrawType(Object_Draw_Type type)
{
	m_draw_type = type;
}

void Object::SetIsDead(bool condition)
{
	isdead = condition;
}


Mesh& Object::GetMesh()
{
    return m_mesh;
}

Transform& Object::GetTransform()
{
    return m_transform;
}

