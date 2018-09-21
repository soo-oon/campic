#pragma once
#include <bitset>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

class Input
{
private:
	static std::bitset<GLFW_KEY_LAST> key_pressed;
	static std::bitset<GLFW_KEY_LAST> key_triggered;
	static std::bitset<GLFW_KEY_LAST> key_released;

	static glm::vec2 mousePos;
	static glm::vec2 windowSize;

	static std::bitset<GLFW_MOUSE_BUTTON_LAST> mouse_pressed;
	static std::bitset<GLFW_MOUSE_BUTTON_LAST> mouse_triggered;
	static std::bitset<GLFW_MOUSE_BUTTON_LAST> mouse_doubleclick;
	static std::bitset<GLFW_MOUSE_BUTTON_LAST> mouse_released;

	static bool mouse_trigger;
	static bool key_trigger;

public:
	static void Triggerd_Reset();

	static void Initialize(int width, int height);
	static void Reset(void);

	static void SetKeyPressed(int key, int action);
	static bool IsKeyPressed(int key);
	static bool IsKeyTriggered(int key);
	static bool IsKeyReleased(int key);
	static bool IsKeyAnyPressed();
	static bool IsKeyAnyTriggered();
	static bool IsKeyAnyReleased();

	static void SetMousePos(double x_pos, double y_pos);
	static glm::vec2 GetMousePos();

	static void SetMousePressed(int button, int action);
	static bool IsMousePressed(int button);
	static bool IsMouseTriggered(int button);
	static bool IsMouseDoubleClicked(int button);
	static bool IsMouseReleased(int button);
};