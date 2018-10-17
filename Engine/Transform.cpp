#include "Transform.hpp"
#include "imgui.h"
affine2d Transform::GetModelToWorld() const
{
    affine2d temp = build_translation(translation.x, translation.y)
        * rotation_affine(rotation)
        * nonuniform_scale_affine(scale.x, scale.y);

    if (parent != nullptr)
    {
        const Transform* temp_parent_transform = this;
        while (temp_parent_transform->parent)
        {
            affine2d temp_affine2d = build_translation(temp_parent_transform->parent->translation.x,
                                                       temp_parent_transform->parent->translation.y)
                * rotation_affine(temp_parent_transform->parent->rotation)
                * nonuniform_scale_affine(temp_parent_transform->parent->scale.x,
                                          temp_parent_transform->parent->scale.y);

            temp_affine2d *= temp;
            temp = temp_affine2d;
            temp_parent_transform = temp_parent_transform->parent;
        }
        return temp;
    }
    return temp;
}
void Transform::Imgui_Transform()
{
	ImGui::SliderFloat("translation_x", &translation.x, -400,400);
	ImGui::SliderFloat("translation_y", &translation.y, -400, 400);
	ImGui::SliderFloat("scale_x", &scale.x, -200, 500);
	ImGui::SliderFloat("scale_y", &scale.y, -200, 500);
	ImGui::SliderFloat("rotation", &rotation, 0, 1000);
	ImGui::SliderFloat("depth", &depth, 0, 1);
}
affine2d Transform::GetTRS()
{
    return build_translation(translation.x,
        translation.y)
        * rotation_affine(rotation)
        *nonuniform_scale_affine(scale.x, scale.y);
}


affine2d Transform::GetWorldToModel() const
{
    affine2d trans_ = build_translation(-translation.x, -translation.y);
    affine2d rotate_ = rotation_affine(-rotation);
    affine2d scale_ = nonuniform_scale_affine(1 / scale.x, 1 / scale.y);

    affine2d temp = scale_ * rotate_ * trans_;

    const Transform* temp_parent_transform = this;

    if (parent != nullptr)
    {
        while (temp_parent_transform->parent)
        {
            affine2d trans_parent = build_translation(-temp_parent_transform->parent->translation.x,
                                                      -temp_parent_transform->parent->translation.y);
            affine2d rotate_parent = rotation_affine(-temp_parent_transform->parent->rotation);
            affine2d scale_parent = nonuniform_scale_affine(1 / temp_parent_transform->parent->scale.x,
                                                            1 / temp_parent_transform->parent->scale.y);

            affine2d temp_parent = scale_parent * rotate_parent * trans_parent;

            temp_parent *= temp;
            temp = temp_parent;
            temp_parent_transform = temp_parent_transform->parent;
        }
        return temp;
    }
    return temp;
}

float Transform::CalculateWorldDepth() const
{
    float temp_depth = depth;

    const Transform* temp_parent = parent;

    if (parent != nullptr)
    {
        while (temp_parent)
        {
            temp_depth += temp_parent->depth;
            temp_parent = temp_parent->parent;
        }
        return temp_depth;
    }
    return temp_depth;
}

float Transform::GetDepth() const
{
    return depth;
}

void Transform::SetDepth(float depth_value)
{
    depth = depth_value;
}

vector2 Transform::GetTranslation() const
{
    return translation;
}

void Transform::SetTranslation(const vector2& translation_affin2d)
{
    translation = translation_affin2d;
}

vector2 Transform::GetScale() const
{
    return scale;
}

void Transform::SetScale(const vector2& scale_value)
{
    scale = scale_value;
}

float* Transform::GetRotation()
{
    return &rotation;
}

void Transform::SetRotation(float rotation_value)
{
    rotation = rotation_value;
}
