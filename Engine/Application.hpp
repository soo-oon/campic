#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "Timer.hpp"
#include <string>
#include "Input.hpp"

class Application
{
public:
    Application() : screenSize(1280, 960)
    {};
    
    ~Application(){};

    bool Initialize();
    void Update();

	void Key_Poll_Event();

    void ShutDown();

    void FullScreen();

	void PollEvent();

	GLFWmonitor* monitor;
        const GLFWvidmode* mode;

    GLFWwindow* GetWindow() { return window; }

    bool Exit = false;

private:
    GLFWwindow* window = nullptr;
    int frame_count = 0;
    float frame_time = 0.0f;

    bool fullScreenMode = false;

    std::string title;
    Timer Game_Timer{};
    vector2 screenSize{};
    vector2 fullscreenSize{};
};