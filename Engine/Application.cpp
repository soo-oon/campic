/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Application.cpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

#include "Application.hpp"
#include <iostream>
#include <stdio.h>
#include "Engine.hpp"
#include "Graphics.hpp"
#include <memory>
#include <string>
#include "imgui_impl_glfw.h"

Application Application_;

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

	//mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
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
	srand((unsigned)time(NULL));

	int w, h;
	glfwGetWindowSize(window, &w, &h);
	real_screenSize.x = static_cast<float>(w);
	real_screenSize.y = static_cast<float>(h);

    return true;
}

void Application::Update(float dt)
{
	fpsEllapsedTime += dt;
	++fpsFrames;
	if (fpsEllapsedTime >= 1.0f)
	{
		
		fps = std::to_string(int(fpsFrames / fpsEllapsedTime));
		title += fps;
		fpsEllapsedTime = 0;
		fpsFrames = 0;
		glfwSetWindowTitle(window, title.c_str());
		title = "Engine ver 0.1 ";
	}

	Input::Triggerd_Reset();
	//glfwSwapBuffers(window);

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

void Application::FullScreen()
{
    if (fullScreenMode)
    {
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        monitor = glfwGetPrimaryMonitor();
        glfwSetWindowMonitor(window, monitor, 0, 0, static_cast<int>(mode->width), static_cast<int>(mode->height), 0);

		int w, h;
		glfwGetWindowSize(window, &w, &h);
		real_screenSize.x = (float)w;
		real_screenSize.y = (float)h;
    }
    else
    {
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        glfwSetWindowMonitor(window, nullptr, (mode->width / 2) - static_cast<int>(screenSize.x / 2),
                             (mode->height / 2) - static_cast<int>(screenSize.y / 2),
                             static_cast<int>(screenSize.x), static_cast<int>(screenSize.y), 0);

		int w, h;
		glfwGetWindowSize(window, &w, &h);
		real_screenSize.x = (float)w;
		real_screenSize.y = (float)h;
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
		ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
    }

	void DropCallBack(GLFWwindow* window, int count, const char** paths)
	{
		std::string path(paths[0]);
		//Imgui_System::soundlist.push_back(path);
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
		ImGui_ImplGlfw_ScrollCallback(window, x_offset, y_offset);
    }
}
