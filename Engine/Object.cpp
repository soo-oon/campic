#include "Object.hpp"

void Object::AddComponent(Component* component)
{
	components.push_back(component);
	component->Initialize();
}

Component* Object::GetComponent(unsigned ID)
{
	for (auto i : components)
	{
		if (i->type == ID)
			return i;
	}
	return nullptr;
}

void Object::SetMesh(Mesh mesh_)
{
	mesh = mesh_;
}

void Object::SetTransform(Transform transform_)
{
	transform = transform_;
}

Mesh& Object::GetMesh()
{
	return mesh;
}

Transform& Object::GetTransform()
{
	return transform;
}
