/******************************************************************************/
/*!
\file   Transform.hpp
\author Choi Jin Hyun
\par    email: jinhyun175@gmail.com
\par    DigiPen login: jinhyun.choi
\par    Course: CS230
\par    Assignment #7
\date   6/16/2018
*/
/******************************************************************************/
#pragma once

#include <glm/vec2.hpp>
#include <glm/mat3x3.hpp>

class Transform
{
public:
    Transform() = default;
    glm::mat3 GetModelToWorld() const;
    glm::mat3 GetWorldToModel() const;

    float CalculateWorldDepth() const;
    float GetDepth() const;
    void SetDepth(float depth_value);

    glm::vec2 GetTranslation() const;
    void SetTranslation(const glm::vec2& translation_affin2d);

	glm::vec2 GetScale() const;
    void SetScale(const glm::vec2& scale_value);

    float GetRotation() const;
    void SetRotation(float rotation_value);

    const Transform* GetParent() const;
    void SetParent(const Transform* const transform_parent);

private:
	glm::vec2 translation{};
	glm::vec2 scale{ 1.0f, 1.0f };
    float rotation = 0.0f;
    float depth = 0.0f;
    const Transform* parent = nullptr;
};