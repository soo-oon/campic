#include "Test_Level.hpp"
#include "Capture.hpp"
#include "Projectile.hpp"
#include "Font.hpp"

void Test_Level::Initialize()
{
	Object* font = new Object();

	font->AddComponent(new Font(L"asset/font/sansation.fnt", L"HI!"));
	font->SetTranslation({-500, 0});
	font->SetScale({ 2.5});
	font->GetComponentByTemplate<Font>()->SetFillColor(Colors::Black);

	Objectmanager_.AddObject(font);
//	Objectmanager_.AddObject(position_check);
}

void Test_Level::Update(float dt)
{
}

void Test_Level::ShutDown()
{
}
