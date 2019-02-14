/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Application.hpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "Input.hpp"
#include "vector2.hpp"
#include "State.hpp"

class Graphics;
class Objectmanager;


class Application
{
public:
    bool Initialize();
    void Update(float dt);
    void Quit();

	GLFWwindow* GetWindow() { return window; }

        vector2 GetScreenSize() { return screenSize; }
    void Key_Poll_Event();
    void PollEvent();
    void FullScreen();

private:
	float fpsEllapsedTime = 0;
	int fpsFrames = 0;

    GLFWmonitor* monitor = nullptr;
    const GLFWvidmode* mode = nullptr;

    GLFWwindow* window = nullptr;
    bool fullScreenMode = false;

    std::string title;
    vector2 screenSize;
};

extern Application Application_;
