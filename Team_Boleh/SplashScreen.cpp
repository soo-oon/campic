#include "SplashScreen.hpp"
#include <iostream>

void SplashScreen::Initialize()
{
	GetObjectManager()->AddObject("Digipen_Logo");
	GetObjectManager()->AddObject("BackGround");

	logo = GetObjectManager()->FindObject("Digipen_Logo").get();
	logo->SetTranslation({ 0,0 });
	logo->SetScale({ 300, 150 });
	logo->SetMesh(mesh::CreateBox());
	logo->AddComponent(new Sprite());
	logo->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/DigiPen_.png");

	background = GetObjectManager()->FindObject("BackGround").get();
	background->SetTranslation({ 0,0 });
	background->SetMesh(mesh::CreateBox());
	background->SetDepth(0.9f);
	background->AddComponent(new Sprite());
	background->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/UI/Menu_background.png");
}

void SplashScreen::Update(float dt)
{
	background->SetScale(GetStateScreenSize());

	time_count += dt;

	if (logo->GetTransform().GetScale().x < 920.0f && 
		logo->GetTransform().GetScale().y < 420.0f )
	{
		logo->SetScale({ logo->GetTransform().GetScale().x + 220 * dt,
		 logo->GetTransform().GetScale().y + 55 * dt });
	}

	if(time_count > 3.5f)
		ChangeLevel("StartMenu");
}


void SplashScreen::ShutDown()
{
}
