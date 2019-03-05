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
//#include <iostream>

void Object::AddComponent(Component* component)
{
    components.push_back(component);
}

void Object::Add_Init_Component(Component* component)
{
    component->Initialize(this);
    components.push_back(component);
}

void Object::SetMesh(Mesh mesh)
{
    object_mesh = mesh;
}

void Object::SetTranslation(const vector2& position)
{
	transform.SetTranslation(position);
}

void Object::SetScale(const vector2& scale)
{
	transform.SetScale(scale);

}

void Object::SetRotation(const float& rotation)
{
    transform.SetRotation(rotation);
}

void Object::SetDepth(const float& depth)
{
    transform.SetDepth(depth);
}

void Object::SetParent(const Transform* transform_)
{
	transform.SetParent(transform_);

	////arctan --> atan2
	//auto temp = transform.GetWorldToModel();
	//affine2d rotate_ = rotation_affine(-transform.GetRotation());

	//temp *= rotate_;

	//transform.SetTranslation({ temp.affine[0][2], temp.affine[1][2] });
	//transform.SetScale({ temp.affine[0][0], temp.affine[1][1] });
}

void Object::SetGravity(float gravity_own)
{
	gravity = gravity_own;
}



float Object::GetGravity()
{
	return gravity;
}


Mesh& Object::GetMesh()
{
    return object_mesh;
}

Transform& Object::GetTransform()
{
    return transform;
}

