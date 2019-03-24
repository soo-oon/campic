#include "HUD_Level.hpp"
#include "HUD.hpp"
#include <iostream>
#include "Graphics.hpp"
#include "Player.hpp"

void HUD_Level::Initialize()
{
	g_Option = new Object();
	g_Option->SetScale({ 500, 500 });
	g_Option->SetDepth(-0.5f);
	g_Option->SetMesh(mesh::CreateBox(1, { 255,0,0,255 }));

	g_Option->SetObjectType(ObjectType::None);
	g_Option->GetMesh().Invisible();

	HUD_.Toggle_HUD_Active();

	//Objectmanager_.AddObject(g_Option);
}

void HUD_Level::Update(float dt)
{
	if (Input::IsKeyTriggered(GLFW_KEY_ESCAPE))
	{
		if (g_Option->GetMesh().IsVisible())
			g_Option->GetMesh().Invisible();
		else
			g_Option->GetMesh().Visible();
	}
}

void HUD_Level::ShutDown()
{
}
