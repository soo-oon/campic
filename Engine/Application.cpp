#include "Application.hpp"
#include <iostream>
#include <stdio.h>
#include "Engine.hpp"

namespace
{
	void errorCallback(int errorCode, const char* errorDescription);
	void window_resized(GLFWwindow* window, int width, int height);
	void KeyCallback(GLFWwindow* window, int key, int scancode
		, int action, int mods);
	void MousePositionCallback(GLFWwindow* window, double x_pos, double y_pos);
	void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
}


bool Application::Initialize()
{
	glfwSetErrorCallback(errorCallback);

	if (!glfwInit())
	{
		std::cerr << "GLFW Initialize failed" << '\n';
		return false;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);	// 4x anti

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
	window = glfwCreateWindow(static_cast<int>(screenSize.x), static_cast<int>(screenSize.y), "Engine ver 0.1 ", NULL, NULL);

	mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	glfwSetWindowMonitor(window, NULL, (mode->width/2) - static_cast<int>(screenSize.x/2), (mode->height/2) - static_cast<int>(screenSize.y/2),
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

void Application::Update(float /*dt*/)
{
	Input::Triggerd_Reset();
	FullScreen();

	glfwSwapBuffers(window);

	PollEvent();
}

void Application::Key_Poll_Event()
{
	if (Input::IsKeyTriggered(GLFW_KEY_F))
	{
		fullScreenMode = !fullScreenMode;
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
        monitor = glfwGetPrimaryMonitor();
        glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, 0);
    }
    else
    {
        glfwSetWindowMonitor(window, nullptr, (mode->width / 2) - static_cast<int>(screenSize.x / 2), (mode->height / 2) - static_cast<int>(screenSize.y / 2),
            static_cast<int>(screenSize.x), static_cast<int>(screenSize.y), 0);
    }
}

void Application::PollEvent()
{
	glfwPollEvents();
	Key_Poll_Event();
}

namespace
{
	void errorCallback(int errorCode, const char* errorDescription)
	{
		fprintf(stderr, "Error: %s\n", errorDescription);
	}

	void window_resized(GLFWwindow* window, int width, int height) 
        {
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
	}

	void KeyCallback(GLFWwindow* window, int key, int scancode
		, int action, int mods)
	{
		Input::SetKeyPressed(key, action);
	}

	void MousePositionCallback(GLFWwindow* window, double x_pos, double y_pos)
	{
		Input::SetMousePos(x_pos, y_pos);
	}

	void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		Input::SetMousePressed(button, action);
	}
}
