#include "Camera.hpp"
#include "matrix2.hpp"
#include "Input.hpp"
#include <iostream>

Camera::Camera(vector2 camera_center, vector2 camera_up)
	: center(camera_center), up(camera_up)
{}

bool Camera::Initialize(Object* Ob)
{
	object = Ob;
	return true;
}

void Camera::Update(float dt)
{
	if (Input::IsKeyTriggered(GLFW_KEY_C))
	{
		ResetUp();
	}

	if(Input::IsKeyPressed(GLFW_KEY_UP))
	{
		MoveUp(3.0f);
	}
	if (Input::IsKeyPressed(GLFW_KEY_DOWN))
	{
		MoveUp(-3.0f);
	}
	if (Input::IsKeyPressed(GLFW_KEY_LEFT))
	{
		MoveRight(-3.0f);
	}
	if (Input::IsKeyPressed(GLFW_KEY_RIGHT))
	{
		MoveRight(3.0f);
	}


	if (Input::MouseWheelScroll() > 0 && zoom <= 20.0f)
	{
		zoom += 0.05f;
	}
	else if(Input::MouseWheelScroll() < 0 && zoom > 0.2f)
	{
		zoom -= 0.05f;
	}
}

void Camera::Delete()
{
}

vector2 Camera::GetCenter() const
{
	return center;
}

void Camera::SetCenter(vector2 camera_center)
{
	center = camera_center;
}

vector2 Camera::GetUp() const
{
	return up;
}

vector2 Camera::GetRight() const
{
	return right;
}

void Camera::ResetUp(vector2 camera_up)
{
	zoom = 1.0f;
	up.x = camera_up.x;
	up.y = camera_up.y;
	right.x = camera_up.y;
	right.y = camera_up.x;
}

void Camera::MoveUp(float distance)
{
	center += up * distance;
}

void Camera::MoveRight(float distnace)
{
	center += right * distnace;
}

void Camera::Rotate(float angle)
{
	matrix2 rotate = rotation(angle);

	up = rotate * up;
	right = rotate * right;
}

affine2d Camera::CameraToWorld() const
{
	affine2d temp(right.x, up.x, 0, right.y, up.y, 0, center.x, center.y, 1);

	return temp;
}

affine2d Camera::WorldToCamera() const
{
	affine2d temp = { right.x, right.y, 0, up.x, up.y,0, 0,0,1 };
	affine2d translation = build_translation(-center.x, -center.y);

	temp *= translation;

	return temp;
}

