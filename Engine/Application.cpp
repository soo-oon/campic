#include "Application.hpp"
#include <iostream>
#include <stdio.h>
#include "Engine.hpp"
#include "Graphics.hpp"
#include <memory>
#include <string>

namespace
{
    void Window_Exit(GLFWwindow* window);
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
    screenSize = vector2{1280, 960};
    temp_size = screenSize;
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x anti
	// We use OpenGL 3.3 version 
	const char* glsl_version = "#version 300 es";
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

	//Imgui Setup
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	unsigned char* pixels;
	int width, height;
	io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImGui::StyleColorsDark();

	glfwSetWindowSizeCallback(window, window_resized);
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MousePositionCallback);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
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

void Application::Update(float /*dt*/)
{
    Input::Triggerd_Reset();
    glfwSwapBuffers(window);
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

void Application::SetDispalyAreaSize(Graphics* graphics)
{
    int w, h;

    glfwGetWindowSize(window, &w, &h);
    screenSize.x = static_cast<float>(w);
    screenSize.y = static_cast<float>(h);
    graphics->SetDisplaySize_G(screenSize);
}

void Application::GetObjectManager(Objectmanager* objectmanager)
{
	// Imgui draw/loop
	bool show_demo_window = true;

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	//ImGui::ShowDemoWindow(&show_demo_window);
	int w, h;
	glfwGetWindowSize(window, &w, &h);
	

	ImGui::Begin("Example Level");
	const char* object_list[3] = {0};
	
	int i = 0;
	for (std::map<std::string, std::unique_ptr<Object>>::iterator it = objectmanager->GetObjectMap().begin(); 
		it != objectmanager->GetObjectMap().end(); ++it)
	{
		object_list[i] = (*it).first.c_str();
		++i;
	}
	static const char* current_object = object_list[0];

	if (ImGui::BeginCombo("ObjectList", current_object))
	{
		for (int j = 0; j < IM_ARRAYSIZE(object_list); j++)
		{
			bool is_selected = (current_object == object_list[j]); // You can store your selection however you want, outside or inside your objects
			if (ImGui::Selectable(object_list[j], is_selected))
			{
				current_object = object_list[j];
			}
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

	objectmanager->FindObject(current_object)->GetTransform().Imgui();

	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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
