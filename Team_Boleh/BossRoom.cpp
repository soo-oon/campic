#include "BossRoom.h"
#include "Application.hpp"

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
    Objectmanager_.AddObject(background);
}

void BossRoom::Update(float dt)
{
}

void BossRoom::ShutDown()
{
    UnLoad();
}
