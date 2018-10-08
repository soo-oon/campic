#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "System.hpp"
#include "Input.hpp"
#include "vector2.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "../Team_Boleh/example_level.hpp"

class Graphics;
class Objectmanager;

class Application : public System
{
public:
    ~Application()
    {
    };

    bool Initialize() override;
    void Update(float dt) override;
    void Quit() override;


	void SetDispalyAreaSize(Graphics* graphics);
	void GetObjectManager(Objectmanager* objectmanager);
	
    void Key_Poll_Event();
    void PollEvent();
    void FullScreen();

private:
    GLFWmonitor* monitor = nullptr;
    const GLFWvidmode* mode = nullptr;
    GLFWmonitor* mode_screen = nullptr;

    GLFWwindow* window = nullptr;
    bool fullScreenMode = false;

    std::string title;
    vector2 screenSize;
    vector2 temp_size{};
};
