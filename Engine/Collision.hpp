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

enum class Filter
{
    Jump,
    Speed,
    None
};
class Collision : public Component
{
public:
    Collision(CollisionType type_ = box_, vector2 size = {1.f} ) : type(type_)
    {
        collision_transform.SetScale(size);
    }

    bool Initialize(Object* Ob) override;
    void Update(float dt) override;
    void Delete() override;

    void Compute_AABB(Mesh mesh, int num_point);

    void ChangeCollisionBoxScale(vector2 scale) { collision_transform.SetScale(scale); }
    void ChangeCollisionBoxTranslation(vector2 translation) { collision_transform.SetTranslation(translation); }

    void ToggleIsDoor();


public:
    void SetIsGet(bool get) { isGet = get; }
    void SetCollisionType(CollisionType type_) { type = type_; }
    void SetIsDoorClose();
    void SetIsGround(bool ground) { isGround = ground; }
    void SetIsCapobj(bool cap) { isCapobj = cap; }
    void SetIsStopped(bool s) { isStopped = s; }
    void SetIsLeft(bool l) { isLeft = l; }
    void SetIsLeftTile(bool lt) { isLeftTile = lt; }
    void SetIsRight(bool r) { isRight = r; }
    void SetIsRightTile(bool rt) { isRightTile = rt; }
    void SetIsCelling(bool cell) { isCelling = cell; }
    void SetCollisionScale(vector2 size_);
    void SetJumpingitutionType(RestitutionType restitution);
    void SetFilter(Filter filter) { m_filter = filter; }
	void SetIsCollideItem(bool condition) { isItem = condition; }

public:
    bool GetisGet() { return isGet; }
    bool GetIsDoor();
    bool GetIsGround() { return isGround; }
    bool GetIsCapobj() { return isCapobj; }
    bool GetIsStopped() { return isStopped; }
    bool GetIsLeft() { return isLeft; }
    bool GetIsLeftTile() { return isLeftTile; }
    bool GetIsRight() { return isRight; }
    bool GetIsRightTile() { return isRightTile; }
    bool GetIsCelling() { return isCelling; }
	bool GetIsCollideItem() {return isItem;}

    Filter GetFilter() { return m_filter; }
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
    Filter m_filter = Filter::None;
    std::vector<vector2> collision_TRS;
    Mesh collision_mesh{};
    float height = 0, width = 0;
    bool isGet = false;
    bool isGround = false;
    bool isCapobj = false;
    bool isLeftTile = false;
    bool isRightTile = false;
    bool isStopped = false;
    bool isLeft = false;
    bool isRight = false;
    bool isCelling = false;
    bool isdoor = false;
	bool isItem = false;
};
