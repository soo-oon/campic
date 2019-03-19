/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Camera.hpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

#pragma once
#include "Component.hpp"
#include "vector2.hpp"
#include "affine2d.hpp"
#include "Object.hpp"

class Camera : public Component
{
public:	
	template<typename T>
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
	float zoom = 1.0f;
	vector2 center{};
	vector2 up{ 0,1 };
	vector2 right{ 1,0 };
};
