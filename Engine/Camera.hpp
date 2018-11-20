#pragma once
#include "Component.hpp"
#include "vector2.hpp"
#include "affine2d.hpp"
#include "Object.hpp"

class Camera : public Component
{
public:
	//Camera() = default;
	template<typename  T>
	Camera(T* state)
	{
		state->SetCamera();
	}
	Camera(vector2 camera_center, vector2 camera_up);

	bool Initialize(Object* Ob) override;
	void Update(float dt) override;
	void Delete() override;

	float GetZoomValue() { return zoom; }
	vector2 GetCenter() const;
	void SetCenter(vector2 camera_center);
	vector2 GetUp() const;
	vector2 GetRight() const;

	void ResetUp(vector2 camera_up = { 0,1 });

	void MoveUp(float distance);
	void MoveRight(float distnace);
	void Rotate(float angle);

	affine2d CameraToWorld() const;
	affine2d WorldToCamera() const;

private:
	float zoom = 1;
	vector2 center{};
	vector2 up{ 0,1 };
	vector2 right{ 1,0 };
};
