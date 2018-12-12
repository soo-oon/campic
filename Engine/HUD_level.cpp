#include "HUD_level.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include "Graphics.hpp"

void HUD_level::Initialize()
{
	GetObjectManager()->AddObject("hud_box");

	auto window = glfwGetCurrentContext();
	glfwGetWindowSize(window, &screen_w, &screen_h);

	GetObjectManager()->FindObject("hud_box")->SetTranslation({});
	GetObjectManager()->FindObject("hud_box")->SetScale({(float)screen_w, (float)screen_h });
	GetObjectManager()->FindObject("hud_box")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	GetObjectManager()->FindObject("hud_box")->AddComponent(new Sprite());
	GetObjectManager()->FindObject("hud_box")->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/hud.png");
}

void HUD_level::Update(float /*dt*/)
{
	GetObjectManager()->FindObject("hud_box")->SetScale({ (float)screen_w/ Graphics::checking_zoom, (float)screen_h/ Graphics::checking_zoom });
}

void HUD_level::ShutDown()
{
}
