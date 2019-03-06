#include "BossRoom.h"
#include "Application.hpp"
#include "Status.hpp"
#include "Boss.hpp"

void BossRoom::Initialize()
{
    int w, h;
    glfwGetWindowSize(Application_.GetWindow(), &w, &h);

    Object * background = new Object();
    background->SetTranslation({ 0,0 });
    background->SetScale(vector2(static_cast<float>(w), static_cast<float>(h)));
    background->SetMesh(mesh::CreateBox(1, {100,100,100}));
    background->SetDepth(0.9f);
    background->AddComponent(new Sprite("asset/images/background1.png"));
    //background.GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/UI/Menu_background.png");

	Object* boss = new Object();
	boss->SetTranslation({ 0, 250 });
	boss->SetScale({ 300, 300 });
	boss->SetMesh(mesh::CreateBox(1, Colors::White));
	boss->SetDepth(-0.1f);
	boss->AddComponent(new Animation("asset/images/Enemies/Boss_ver1.png", "boss1", 2, 1.0f));
	boss->AddComponent(new Boss(BossSkillType::ShootOut, "asset/images/shot.png", GetPlayerPointer()));
	boss->AddComponent(new Status(ObjectType::Boss, 10, 1, 0, true));

	Objectmanager_.AddObject(background);
	Objectmanager_.AddObject(boss);

}

void BossRoom::Update(float dt)
{
}

void BossRoom::ShutDown()
{
    UnLoad();
}
