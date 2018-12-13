#include "HUD_level.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include "Graphics.hpp"
#include "Player.hpp"
#include "Input.hpp"
#include "status.hpp"
#include "Animation.hpp"

void HUD_level::Initialize()
{
	GetObjectManager()->AddObject("hud_box");
	GetObjectManager()->AddObject("carddeck1");
	GetObjectManager()->AddObject("carddeck2");
	GetObjectManager()->AddObject("HP_Bar");
	GetObjectManager()->AddObject("HP0");
	GetObjectManager()->AddObject("HP1");
	GetObjectManager()->AddObject("HP2");
	GetObjectManager()->AddObject("HP3");
	GetObjectManager()->AddObject("HP4");

	auto window = glfwGetCurrentContext();
	glfwGetWindowSize(window, &screen_w, &screen_h);

	GetObjectManager()->FindObject("hud_box")->SetTranslation({});
	GetObjectManager()->FindObject("hud_box")->SetScale({(float)screen_w, (float)screen_h });
	GetObjectManager()->FindObject("hud_box")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	GetObjectManager()->FindObject("hud_box")->AddComponent(new Sprite());
	GetObjectManager()->FindObject("hud_box")->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/hud_wall.png");

	GetObjectManager()->FindObject("carddeck1")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	GetObjectManager()->FindObject("carddeck1")->AddComponent(new Sprite());
	GetObjectManager()->FindObject("carddeck1")->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/carddeck.png");

	GetObjectManager()->FindObject("carddeck2")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	GetObjectManager()->FindObject("carddeck2")->AddComponent(new Sprite());
	GetObjectManager()->FindObject("carddeck2")->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/carddeck.png");

	GetObjectManager()->FindObject("HP0")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	GetObjectManager()->FindObject("HP0")->AddComponent(new Animation("asset/images/life.png", "heart0", 1, 0, false));
	GetObjectManager()->FindObject("HP0")->GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/life_animated.png", "heart1", 5, 0.1f, false);
	
	GetObjectManager()->FindObject("HP1")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	GetObjectManager()->FindObject("HP1")->AddComponent(new Animation("asset/images/life.png", "heart0", 1, 0, false));
	GetObjectManager()->FindObject("HP1")->GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/life_animated.png", "heart1", 5, 0.1f, false);
	
	GetObjectManager()->FindObject("HP2")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	GetObjectManager()->FindObject("HP2")->AddComponent(new Animation("asset/images/life.png", "heart0", 1, 0, false));
	GetObjectManager()->FindObject("HP2")->GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/life_animated.png", "heart1", 5, 0.1f, false);
	
	GetObjectManager()->FindObject("HP3")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	GetObjectManager()->FindObject("HP3")->AddComponent(new Animation("asset/images/life.png", "heart0", 1, 0, false));
	GetObjectManager()->FindObject("HP3")->GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/life_animated.png", "heart1", 5, 0.1f, false);
	
	GetObjectManager()->FindObject("HP4")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	GetObjectManager()->FindObject("HP4")->AddComponent(new Animation("asset/images/life.png", "heart0", 1, 0, false));
	GetObjectManager()->FindObject("HP4")->GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/life_animated.png", "heart1", 5, 0.1f, false);
}

void HUD_level::Update(float /*dt*/)
{
	std::string path = ".png";
	card_name = obj_hud->FindObject("Player")->GetComponentByTemplate<Player>()->GetCardList();
	auto player_hp = obj_hud->FindObject("Player")->GetComponentByTemplate<Status>()->GetHp();

	if (!first_deck_occupied || !second_deck_occupied)
	{
		if (card_name.size() == 1)
		{
			GetObjectManager()->FindObject("carddeck1")->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/" + card_name.at(0) + path);
			first_deck_occupied = true;
		}
		if (card_name.size() == 2)
		{
			GetObjectManager()->FindObject("carddeck2")->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/" + card_name.at(1) + path);
			second_deck_occupied = true;
		}
	}
	
	if(Input::IsKeyTriggered(GLFW_KEY_T))
	{
		GetObjectManager()->FindObject("carddeck1")->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/carddeck.png");
		GetObjectManager()->FindObject("carddeck2")->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/carddeck.png");
		card_name.clear();
		first_deck_occupied = false;
		second_deck_occupied = false;
	}

	if(player_hp == 4)
	{
		GetObjectManager()->FindObject("HP4")->GetComponentByTemplate<Animation>()->ChangeAnimation("heart1");
	}
	else if (player_hp == 3)
	{
		GetObjectManager()->FindObject("HP3")->GetComponentByTemplate<Animation>()->ChangeAnimation("heart1");
	}
	else if (player_hp == 2)
	{
		GetObjectManager()->FindObject("HP2")->GetComponentByTemplate<Animation>()->ChangeAnimation("heart1");
	}
	else if (player_hp == 1)
	{
		GetObjectManager()->FindObject("HP1")->GetComponentByTemplate<Animation>()->ChangeAnimation("heart1");
	}
	else if (player_hp == 0)
	{
		GetObjectManager()->FindObject("HP0")->GetComponentByTemplate<Animation>()->ChangeAnimation("heart1");
	}

	auto window = glfwGetCurrentContext();
	glfwGetWindowSize(window, &screen_w, &screen_h);
	GetObjectManager()->FindObject("hud_box")->SetScale({ (float)screen_w/ Graphics::checking_zoom, (float)screen_h/ Graphics::checking_zoom });
	GetObjectManager()->FindObject("carddeck1")->SetScale({ 100 / Graphics::checking_zoom, 150 / Graphics::checking_zoom });
	GetObjectManager()->FindObject("carddeck2")->SetScale({ 100 / Graphics::checking_zoom, 150 / Graphics::checking_zoom });
	GetObjectManager()->FindObject("carddeck1")->SetTranslation({ ((float)screen_w/2 - 150) / Graphics::checking_zoom, (-(float)screen_h/2 + 75) / Graphics::checking_zoom });
	GetObjectManager()->FindObject("carddeck2")->SetTranslation({ ((float)screen_w/2 - 50)  / Graphics::checking_zoom, (-(float)screen_h/2 + 75) / Graphics::checking_zoom });

	GetObjectManager()->FindObject("HP0")->SetScale({ 50 / Graphics::checking_zoom, 50 / Graphics::checking_zoom });
	GetObjectManager()->FindObject("HP0")->SetTranslation({ -520 / Graphics::checking_zoom, ((float)screen_h / 2 - 30) / Graphics::checking_zoom });
	GetObjectManager()->FindObject("HP1")->SetScale({ 50 / Graphics::checking_zoom, 50 / Graphics::checking_zoom });
	GetObjectManager()->FindObject("HP1")->SetTranslation({ -470 / Graphics::checking_zoom, ((float)screen_h / 2 - 30) / Graphics::checking_zoom });
	GetObjectManager()->FindObject("HP2")->SetScale({ 50 / Graphics::checking_zoom, 50 / Graphics::checking_zoom });
	GetObjectManager()->FindObject("HP2")->SetTranslation({ -420 / Graphics::checking_zoom, ((float)screen_h / 2 - 30) / Graphics::checking_zoom });
	GetObjectManager()->FindObject("HP3")->SetScale({ 50 / Graphics::checking_zoom, 50 / Graphics::checking_zoom });
	GetObjectManager()->FindObject("HP3")->SetTranslation({ -370 / Graphics::checking_zoom, ((float)screen_h / 2 - 30) / Graphics::checking_zoom });
	GetObjectManager()->FindObject("HP4")->SetScale({ 50 / Graphics::checking_zoom, 50 / Graphics::checking_zoom });
	GetObjectManager()->FindObject("HP4")->SetTranslation({ -320 / Graphics::checking_zoom, ((float)screen_h / 2 - 30) / Graphics::checking_zoom });
}

void HUD_level::ShutDown()
{
}
