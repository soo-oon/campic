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

#include "vector2.hpp"
#include "affine2d.hpp"

class Transform
{
public:
    Transform() = default;
    affine2d GetModelToWorld() const;
    affine2d GetWorldToModel() const;

    float CalculateWorldDepth() const;
    float GetDepth() const;
    void SetDepth(float depth_value);

    vector2 GetTranslation() const;
    void SetTranslation(const vector2& translation_affin2d);

    vector2 GetScale() const;
    void SetScale(const vector2& scale_value);

    float GetRotation() const;
    void SetRotation(float rotation_value);

    const Transform* GetParent() const;
    void SetParent(const Transform* transform_parent);

private:
    vector2 translation{};
    vector2 scale{1.0f, 1.0f};
    float rotation = 0.0f;
    float depth = 0.0f;
    const Transform* parent = nullptr;
};
