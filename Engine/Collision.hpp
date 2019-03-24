/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Collision.hpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Jung Soon Woo
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

#pragma once
#include "Objectmanager.hpp"
#include "Mesh.hpp"

enum RestitutionType
{
    bounce,
    stop,
    ghost,
    damaged,
    get,
    exit_,
    none,
    size
};

enum class CollisionState
{
    damaged,
    collided,
};

class Collision : public Component
{
public:
    Collision(CollisionType type_ = box_) : type(type_)
    {
    }

    bool Initialize(Object* Ob) override;
    void Update(float dt) override;
    void Delete() override;

    void Compute_AABB(Mesh mesh, int num_point);

    void ChangeCollisionBoxScale(vector2 scale) { collision_transform.SetScale(scale); }
    void ChangeCollisionBoxTranslation(vector2 translation) { collision_transform.SetTranslation(translation); }

    void ToggleIsDamaged();
    bool GetIsDamaged();
    void Nohit();
    void ToggleIsDoor();


public:
    void SetIsGet(bool get) { isGet = get; }
    void SetCollisionType(CollisionType type_) { type = type_; }
    void SetIsDoorClose();
    void SetIsGround(bool ground) { isGround = ground; }
    void SetIsCapobj(bool cap) { isCapobj = cap; }
    void SetCollisionScale(vector2 size_);
    void SetJumpingitutionType(RestitutionType restitution);

public:
    bool GetisGet() { return isGet; }
    bool GetIsDoor();
    bool GetIsGround() { return isGround; }
    bool GetIsCapobj() { return isCapobj; }
    CollisionType& GetCollisionType();
    std::vector<vector2> GetCollisionCalculateTRS();
    Mesh& GetCollsionMesh();
    Transform& GetCollisionTransform();
    RestitutionType& GetJumpingitutionType();


    //void SetCollision

private:
    vector2 collision_m_previous_position;
    RestitutionType restitution_ = none;
    Transform collision_transform{};
    CollisionType type = box_;
    std::vector<vector2> collision_TRS;
    Mesh collision_mesh{};
    float height = 0, width = 0;
    bool isGet = false;
    bool isGround = false;
    bool isCapobj = false;
    bool isdamaged = false;
    bool isdoor = false;
};
