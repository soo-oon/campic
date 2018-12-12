﻿#include "Application.hpp"
#include <iostream>
#include <stdio.h>
#include "Engine.hpp"
#include "Graphics.hpp"
#include <memory>
#include <string>
#include "imgui_impl_glfw.h"
#include "Imgui_System.hpp"

namespace
{
    void Window_Exit(GLFWwindow* window);
    void errorCallback(int errorCode, const char* errorDescription);
    void window_resized(GLFWwindow* window, int width, int height);
    void KeyCallback(GLFWwindow* window, int key, int scancode
                     , int action, int mods);
    void MousePositionCallback(GLFWwindow* window, double x_pos, double y_pos);
    void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	void MouseWheelScroll(GLFWwindow* window, double x_offset, double y_offset);
	void DropCallBack(GLFWwindow* window, int count, const char** paths);
}


bool Application::Initialize()
{
    glfwSetErrorCallback(errorCallback);

    if (!glfwInit())
    {
        std::cerr << "GLFW Initialize failed" << '\n';
        return false;
    }
    screenSize = vector2{1280, 960};
    temp_size = screenSize;
	
    //glfwWindowHint(GLFW_SAMPLES, 4); // 4x anti
	
	// We use OpenGL 3.3 version 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // To make MacOS happy
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // We don't use the past OpenGL
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


    /* window make 
    4 parameter : full screen mode -> if want to use glfwGetPrimaryMonitor(),
     5 patameter : share resources*/
    window = glfwCreateWindow(static_cast<int>(screenSize.x), static_cast<int>(screenSize.y), "Engine ver 0.1 ",
                              nullptr, nullptr);

    mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    glfwSetWindowMonitor(window, nullptr, (mode->width / 2) - static_cast<int>(screenSize.x / 2),
                         (mode->height / 2) - static_cast<int>(screenSize.y / 2),
                         static_cast<int>(screenSize.x), static_cast<int>(screenSize.y), 0);

    title = "Engine ver 0.1 ";

    if (!window)
    {
        std::cerr << "Fail to make window" << '\n';
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);

	glfwSetWindowSizeCallback(window, window_resized);
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MousePositionCallback);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	glfwSetScrollCallback(window, MouseWheelScroll);
	glfwSetDropCallback(window, DropCallBack);
	glfwSetWindowCloseCallback(window, Window_Exit);

    Input::Initialize(static_cast<int>(screenSize.x), static_cast<int>(screenSize.y));

    glewExperimental = GL_TRUE;
    GLenum errorCode = glewInit();

    if (GLEW_OK != errorCode)
    {
        std::cerr << "Error: Fail to Initialize GLFW" <<
            glewGetErrorString(errorCode) << '\n';

        glfwTerminate();
        return false;
    }
    glfwSwapInterval(true);

    return true;
}

void Application::Update(float dt)
{
	fpsEllapsedTime += dt;
	++fpsFrames;
	if (fpsEllapsedTime >= 1.0f)
	{
		
		title += std::to_string(int(fpsFrames / fpsEllapsedTime));
		fpsEllapsedTime = 0;
		fpsFrames = 0;
		glfwSetWindowTitle(window, title.c_str());
		title = "Engine ver 0.1 ";
	}

    Input::Triggerd_Reset();
#if _DEBUG
    //glfwSwapBuffers(window);
#else
	glfwSwapBuffers(window);
#endif
    PollEvent();
}

void Application::Key_Poll_Event()
{
    if (Input::IsKeyTriggered(GLFW_KEY_F))
    {
        fullScreenMode = !fullScreenMode;
        FullScreen();
    }
}

void Application::Quit()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::SetDispalyAreaSize(Graphics* graphics, State* current_state)
{
    int w, h;

    glfwGetWindowSize(window, &w, &h);
    screenSize.x = static_cast<float>(w);
    screenSize.y = static_cast<float>(h);
    graphics->SetDisplaySize_G(screenSize, current_state);

	current_state->SetStateScreenSize({ static_cast<float>(w),static_cast<float>(h) });
}

void Application::FullScreen()
{
    if (fullScreenMode)
    {
        monitor = glfwGetPrimaryMonitor();
        //int w, h;
		//glfwGetWindowSize(window, &w, &h);
        //screenSize.x = static_cast<float>(w);
        //screenSize.y = static_cast<float>(h);
        glfwSetWindowMonitor(window, monitor, 0, 0, static_cast<int>(mode->width), static_cast<int>(mode->height), mode->refreshRate);
    }
    else
    {
        //int w, h;
        //glfwGetWindowSize(window, &w, &h);
		screenSize.x = temp_size.x;
		screenSize.y = temp_size.y;
        glfwSetWindowMonitor(window, nullptr, (mode->width / 2) - static_cast<int>(screenSize.x / 2),
                             (mode->height / 2) - static_cast<int>(screenSize.y / 2),
                             static_cast<int>(screenSize.x), static_cast<int>(screenSize.y), 0);
    }
}

void Application::PollEvent()
{
	glfwSwapInterval(true);
    glfwPollEvents();
    Key_Poll_Event();
}

namespace
{
    void Window_Exit(GLFWwindow* window)
    {
        Engine::IsQuit = true;
    }

    void errorCallback(int errorCode, const char* errorDescription)
    {
        fprintf(stderr, "Error: %s\n", errorDescription);
    }

    void window_resized(GLFWwindow* window, int width, int height)
    {
    }

    void KeyCallback(GLFWwindow* window, int key, int scancode
                     , int action, int mods)
    {
		Input::SetKeyPressed(key, action);
#if _DEBUG
		ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
#endif
    }

	void DropCallBack(GLFWwindow* window, int count, const char** paths)
	{
		std::string path(paths[0]);
		Imgui_System::soundlist.push_back(path);
	}

    void MousePositionCallback(GLFWwindow* window, double x_pos, double y_pos)
    {
        Input::SetMousePos(x_pos, y_pos);
    }

    void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
    {
        Input::SetMousePressed(button, action);
    }

	void MouseWheelScroll(GLFWwindow* window, double x_offset, double y_offset)
    {
		Input::SetMouseWheelScroll(x_offset, y_offset);
#if _DEBUG
		ImGui_ImplGlfw_ScrollCallback(window, x_offset, y_offset);
#endif
    }
}
