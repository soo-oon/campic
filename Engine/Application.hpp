#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <string>
#include "System.hpp"
#include "Input.hpp"
#include <glm/vec2.hpp>

class Application : public System
{
public:
    Application() : screenSize(1280, 960)
    {};
    
    ~Application(){};

    bool Initialize() override;
    void Update(float dt) override;
    void Quit() override;

    void Key_Poll_Event();
    void PollEvent();
    void FullScreen();

    bool Exit = false;

private:
    GLFWmonitor* monitor = nullptr;
    const GLFWvidmode* mode = nullptr;

    GLFWwindow* window = nullptr;
    bool fullScreenMode = false;

    std::string title;
    glm::vec2 screenSize{};
    glm::vec2 fullscreenSize{};
};