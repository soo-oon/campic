#pragma once
#include "Application.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "System.hpp"
#include "Objectmanager.hpp"
#include "Animation.hpp"

class Imgui_System: public System
{
public:
	~Imgui_System()
	{
	};

	bool Initialize() override;
	void Update(float dt) override;
	void Quit() override;

	void Draw();
	void ObjectManger();

	void SetWindow(GLFWwindow* window_) { window = window_; }
	void SetObjectManger(Objectmanager* obj_manager) { object_manager = obj_manager; }

private:
	GLFWwindow* window = nullptr;
	Objectmanager* object_manager = nullptr;
	bool show_window = true;
};
