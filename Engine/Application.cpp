#include "Application.hpp"
#include <iostream>
#include <stdio.h>


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

        // 화면 resoultuon 받아 오는 함수를 이용해서 변수에 저장
        mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

        // 화면 생성시 간지 나게 postion잡는다고 계산했습니당
        glfwSetWindowMonitor(window, NULL, (mode->width/2.0f) - (screenSize.x/2.0f), (mode->height/2.0f) - (screenSize.y/2.0f), 
            screenSize.x, screenSize.y, 0);

	title = "Engine ver 0.1 ";

	if (!window)
	{
		std::cerr << "Fail to make window" << '\n';
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);

        // 인풋 관련된 glfw  함수들
	glfwSetWindowSizeCallback(window, window_resized);
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MousePositionCallback);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);

        // 인풋 초기화
	Input::Initialize(screenSize.x, screenSize.y);

	glewExperimental = GL_TRUE;
	GLenum errorCode = glewInit();

	if (GLEW_OK != errorCode)
	{
		std::cerr << "Error: Fail to Initialize GLFW" << 
			glewGetErrorString(errorCode) << '\n';

		glfwTerminate();
		return false;
	}

	glClearColor(1.0, 1.0, 1.0, 1.0);

	glfwSwapInterval(true);

	Game_Timer.Reset();

	return true;
}

void Application::Update()
{
        Input::Triggerd_Reset(); //Trigger 할려면 업데이트 한번 받고 초기화 용으로 나두어야함
	FullScreen();   // Full screen 확인용 함수

        // -- start -- fps 출력하기 위한 함수
	float dt = (float)Game_Timer.GetElapsedSeconds();
	Game_Timer.Reset();

	++frame_count;
	frame_time += dt;

	if (frame_time >= 1.0f)
	{
		auto fps = frame_count / frame_time;
		frame_count = 0;
		frame_time = 0;

		title += std::to_string((int)fps);

		glfwSetWindowTitle(window, title.c_str());
		title = "Engine ver 0.1 ";
	}
        // -- end --

        // -- start -- 화면 랜더 할려면 넣어야하는것들 나중에 display class만들면 한번에 치울거
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);
        //-- end --

	PollEvent(); // 기본 윈도우 컨트롤 하는 키인풋을 처리함 이함수안에 여러 함수 들어가 있음
}

// Save ALL Application Key event
void Application::Key_Poll_Event()
{
	if (Input::IsKeyTriggered(GLFW_KEY_F))
	{
		fullScreenMode = !fullScreenMode;
	}

	if (Input::IsKeyTriggered(GLFW_KEY_ESCAPE))
	{
		Exit = true;
	}
}

// 종료될때
void Application::ShutDown()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

// fullscreen
void Application::FullScreen()
{
    if (fullScreenMode)
    {
        monitor = glfwGetPrimaryMonitor();
        glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, 0);
    }
    else
    {
        glfwSetWindowMonitor(window, NULL, (mode->width / 2.0f) - (screenSize.x / 2.0f), (mode->height / 2.0f) - (screenSize.y / 2.0f),
            screenSize.x, screenSize.y, 0);
    }
}

void Application::PollEvent()
{
	glfwPollEvents();
	Key_Poll_Event();
}


// 그대로 나두어야함 나중에 설명드릴게요
namespace
{
	void errorCallback(int errorCode, const char* errorDescription)
	{
		fprintf(stderr, "Error: %s\n", errorDescription);
	}

	void window_resized(GLFWwindow* window, int width, int height) {
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
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
