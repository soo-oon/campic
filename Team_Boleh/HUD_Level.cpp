#include "HUD_Level.hpp"
#include "HUD.hpp"
#include <iostream>
#include "Graphics.hpp"

void HUD_Level::Initialize()
{
	hp = new Object();
	hp->SetScale(50.0f);
	hp->Set_HUD_Object_Size(hp->GetTransform().GetScale());
	hp->SetMesh(mesh::CreateBox(1, { 255,255,255 }));
	hp->SetTranslation({-Application_.GetScreenSize().x/2 + (hp->GetTransform().GetScale().x/2),
		Application_.GetScreenSize().y/2 - (hp->GetTransform().GetScale().y/2)});
	hp->AddComponent(new Sprite("asset/images/life.png"));

	HUD_.Add_HUD_Object(hp);
}

void HUD_Level::Update(float dt)
{
	hp->SetScale({ hp->Get_Object_HUD_Size().x / Graphics::camera_zoom,hp->Get_Object_HUD_Size().y / Graphics::camera_zoom });
	hp->SetTranslation({ ((-Application_.GetScreenSize().x / 2) + (hp->Get_Object_HUD_Size().x/2)) / Graphics::camera_zoom,
		((Application_.GetScreenSize().y / 2) - (hp->Get_Object_HUD_Size().y/2)) / Graphics::camera_zoom });

	//hp->SetTranslation({ hp->GetTransform().GetTranslation().x + 1, hp->GetTransform().GetTranslation().y});
}

void HUD_Level::ShutDown()
{
}
