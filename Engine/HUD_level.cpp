#include "HUD_level.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include "Graphics.hpp"
#include "Player.hpp"
#include "Input.hpp"

void HUD_level::Initialize()
{
	Load();

	GetObjectManager()->AddObject("hud_box");
	GetObjectManager()->AddObject("carddeck1");
	GetObjectManager()->AddObject("carddeck2");

	auto window = glfwGetCurrentContext();
	glfwGetWindowSize(window, &screen_w, &screen_h);

	GetObjectManager()->FindObject("hud_box")->SetTranslation({});
	GetObjectManager()->FindObject("hud_box")->SetScale({(float)screen_w, (float)screen_h });
	GetObjectManager()->FindObject("hud_box")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	GetObjectManager()->FindObject("hud_box")->AddComponent(new Sprite());
	GetObjectManager()->FindObject("hud_box")->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/hud.png");

	GetObjectManager()->FindObject("carddeck1")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	GetObjectManager()->FindObject("carddeck1")->AddComponent(new Sprite());
	GetObjectManager()->FindObject("carddeck1")->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/carddeck.png");

	GetObjectManager()->FindObject("carddeck2")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	GetObjectManager()->FindObject("carddeck2")->AddComponent(new Sprite());
	GetObjectManager()->FindObject("carddeck2")->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/carddeck.png");
}

void HUD_level::Update(float /*dt*/)
{
	std::string path = ".png";
	card_name = objectmanager->FindObject("player")->GetComponentByTemplate<Player>()->GetCardList();
	if(card_name.size() == 1)
	{
		GetObjectManager()->FindObject("carddeck1")->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/" + card_name.at(0) + path);
	}
	if (card_name.size() == 2)
		GetObjectManager()->FindObject("carddeck2")->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/" + card_name.at(1) + path);

	if(Input::IsKeyTriggered(GLFW_KEY_T))
	{
		GetObjectManager()->FindObject("carddeck1")->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/carddeck.png");
		GetObjectManager()->FindObject("carddeck2")->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/carddeck.png");
		card_name.clear();

	}
	auto window = glfwGetCurrentContext();
	glfwGetWindowSize(window, &screen_w, &screen_h);
	GetObjectManager()->FindObject("hud_box")->SetScale({ (float)screen_w/ Graphics::checking_zoom, (float)screen_h/ Graphics::checking_zoom });
	GetObjectManager()->FindObject("carddeck1")->SetScale({ 100 / Graphics::checking_zoom, 150 / Graphics::checking_zoom });
	GetObjectManager()->FindObject("carddeck2")->SetScale({ 100 / Graphics::checking_zoom, 150 / Graphics::checking_zoom });
	GetObjectManager()->FindObject("carddeck1")->SetTranslation({ ((float)screen_w/2 - 150) / Graphics::checking_zoom, (-(float)screen_h/2 + 75) / Graphics::checking_zoom });
	GetObjectManager()->FindObject("carddeck2")->SetTranslation({ ((float)screen_w/2 - 50)  / Graphics::checking_zoom, (-(float)screen_h/2 + 75) / Graphics::checking_zoom });

}

void HUD_level::ShutDown()
{
}
