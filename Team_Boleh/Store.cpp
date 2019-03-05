#include "Store.h"
#include "Status.hpp"
#include "Application.hpp"

void Store::Initialize()
{
    int w, h;
    glfwGetWindowSize(Application_.GetWindow(), &w, &h);

    Object * background = new Object();
    background->SetTranslation({ 0,0 });
    background->SetScale(vector2(static_cast<float>(w), static_cast<float>(h)));
    background->SetMesh(mesh::CreateBox());
    background->SetDepth(0.9f);
    background->AddComponent(new Sprite("asset/images/store_back.png"));
    //background.GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/UI/Menu_background.png");

    Object* card = new Object();
    card->SetTranslation({ 385, 100 });
    card->SetScale({ 48.f, 60.f });
    card->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
    //card->AddComponent(new Card("Red"));
    card->AddComponent(new Sprite("asset/images/red_soul.png"));
    card->AddComponent(new Collision(box_));
    card->AddComponent(new Status(ObjectType::Item));

    Object* card1 = new Object();
    card1->SetTranslation({ 0, 100 });
    card1->SetScale({ 48.f, 60.f });
    card1->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
    //card1->AddComponent(new Card("Blue"));
    card1->AddComponent(new Sprite("asset/images/blue_soul.png"));
    card1->AddComponent(new Collision(box_));
    card1->AddComponent(new Status(ObjectType::Item));

    Object* armor = new Object();
    armor->SetTranslation({ -385, 100 });
    armor->SetScale({ 64, 64 });
    armor->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
    //card1->AddComponent(new Card("Blue"));
    armor->AddComponent(new Sprite("asset/images/armor.png"));
    armor->AddComponent(new Collision(box_));
    armor->AddComponent(new Status(ObjectType::Item));

    room1 = new Object();
    room1->SetTranslation({ 0,-300 });
    room1->SetScale({ 50.f });
    room1->SetMesh(mesh::CreateBox());
    room1->SetDepth(0.1f);
    room1->AddComponent(new Collision(box_));
    room1->AddComponent(new Status(ObjectType::Door));
    room1->AddComponent(new Sprite("asset/images/door.png"));

    Object* dealer = new Object();
    dealer->SetTranslation({ 0,300 });
    dealer->SetScale({ 128.f });
    dealer->SetMesh(mesh::CreateBox());
    dealer->AddComponent(new Sprite("asset/images/dealer.png"));


    GetPlayerPointer()->SetTranslation(-StateManager_.player_position);

    Objectmanager_.AddObject(dealer);
    Objectmanager_.AddObject(armor);
    Objectmanager_.AddObject(card);
    Objectmanager_.AddObject(card1);
    Objectmanager_.AddObject(room1);
    Objectmanager_.AddObject(background);
}

void Store::Update(float dt)
{
    if (Input::IsKeyTriggered(GLFW_KEY_Q) && room1->GetComponentByTemplate<Collision>()->GetIsDoor())
    {
        StateManager_.player_position = GetPlayerPointer()->GetTransform().GetTranslation();
        ChangeLevel("Room1");
    }
}

void Store::ShutDown()
{
    UnLoad();
}
