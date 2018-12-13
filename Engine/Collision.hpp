#pragma once
#include "Objectmanager.hpp"
#include "Mesh.hpp"

enum class RestitutionType
{
	bounce,
	stop,
	ghost,
	damaged,
        get,
	exit,
	none,
};
enum class CollisionState
{
	damaged,
	collided,
};
class Collision : public Component
{
public:
	Collision(CollisionType type_, vector2 translation_ = {0,0}, 
		vector2 scale_ = {1,1}, float rotation_ = 0) : type(type_)
	{
		collision_transform.SetTranslation(translation_);
		collision_transform.SetScale(scale_);
		//collision_transform.SetRotation(rotation_);
		
	}

	bool Initialize(Object* Ob) override;
	void Update(float dt) override;
	void Delete() override;

	void SetRestitutionType(RestitutionType restitution);
        RestitutionType& GetRestitutionType();

	void Compute_AABB(Mesh mesh, int num_point);

	Mesh& GetCollsionMesh();
	Transform& GetCollisionTransform();

	void ChangeCollisionBoxScale(vector2 scale) { collision_transform.SetScale(scale); }

	CollisionType& GetCollisionType();
	std::vector<vector2> GetCollisionCalculateTRS();
	void ToggleIsDamaged();
	bool GetIsDamaged();
	void Nohit();
	void ToggleIsDoor();
	bool GetIsDoor();
	void SetIsDoorClose();


private:
	RestitutionType restitution_ = RestitutionType::none;
	std::vector<vector2> collision_TRS;
	Mesh collision_mesh{};
	float height =0 , width = 0;
	Transform collision_transform{};
	CollisionType type = box_;
	bool isdamaged = false;
	bool isdoor = false;
};
