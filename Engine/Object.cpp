#include "Object.hpp"

void Object::AddComponent(Component* component)
{
    components.push_back(component);
    component->Initialize(this);
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

void Object::SetTranslation(const vector2& position)
{
    transform.SetTranslation(position);
}

void Object::SetScale(const vector2& scale)
{
    transform.SetScale(scale);
}

void Object::SetRotation(float& rotation)
{
    transform.SetRotation(rotation);
}

void Object::SetDepth(float& depth)
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
    return mesh;
}

Transform& Object::GetTransform()
{
    return transform;
}
