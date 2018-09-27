// Student
// 
// Team_Boleh
// Engine
// Transform.cpp
// 
// 2018
// 09
// 27
// 3:54 PM

#include "Transform.hpp"
#include <glm/gtx/matrix_transform_2d.hpp>

glm::mat3 Transform::GetModelToWorld() const
{
	glm::mat3 rotate_mat3;
	glm::mat3 scale_mat3;
	glm::mat3 temp;

	translate(temp, translation);

	temp *= rotate(rotate_mat3, rotation);
	temp *= glm::scale(scale_mat3, scale);

	if (parent != nullptr)
	{
		const Transform* temp_parent_transform = this;
		while (temp_parent_transform->parent)
		{
			glm::mat3 temp_affine2d = build_translation(temp_parent_transform->parent->translation.x,
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

glm::mat3 Transform::GetWorldToModel() const
{
	glm::mat3 trans_ = build_translation(-translation.x, -translation.y);
	glm::mat3 scale_ = nonuniform_scale_affine(1 / scale.x, 1 / scale.y);
	glm::mat3 rotate_ = rotation_affine(-rotation);

	glm::mat3 temp = scale_ * rotate_ * trans_;

	const Transform* temp_parent_transform = this;

	if (parent != nullptr)
	{
		while (temp_parent_transform->parent)
		{
			glm::mat3 trans_parent = build_translation(-temp_parent_transform->parent->translation.x,
			                                           -temp_parent_transform->parent->translation.y);
			glm::mat3 scale_parent = nonuniform_scale_affine(1 / temp_parent_transform->parent->scale.x,
			                                                 1 / temp_parent_transform->parent->scale.y);
			glm::mat3 rotate_parent = rotation_affine(-temp_parent_transform->parent->rotation);

			glm::mat3 temp_parent = scale_parent * rotate_parent * trans_parent;

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

glm::vec2 Transform::GetTranslation() const
{
	return translation;
}

void Transform::SetTranslation(const glm::vec2& translation_affin2d)
{
	translation = translation_affin2d;
}

glm::vec2 Transform::GetScale() const
{
	return scale;
}

void Transform::SetScale(const glm::vec2& scale_value)
{
	scale = scale_value;
}

float Transform::GetRotation() const
{
	return rotation;
}

void Transform::SetRotation(float rotation_value)
{
	rotation = rotation_value;
}
