#include "Object.hpp"

void Object::AddComponent(Component* component)
{
    components.push_back(component);
    component->Initialize(this);
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
