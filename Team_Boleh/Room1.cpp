#include "Room1.h"
#include "Application.hpp"
#include "Status.hpp"
#include "Enemy.hpp"

void Room1::Initialize()
{
    int w, h;
    glfwGetWindowSize(Application_.GetWindow(), &w, &h);

    Object * background = new Object();
    background->SetTranslation({ 0,0 });
    background->SetScale(vector2(static_cast<float>(w), static_cast<float>(h)));
    background->SetMesh(mesh::CreateBox(1,{255,100,100}));
    background->SetDepth(0.9f);
    background->AddComponent(new Sprite("asset/images/background1.png"));
    //background.GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/UI/Menu_background.png");

    store = new Object();
    store->SetTranslation({ 0,300 });
    store->SetScale({ 50.f });
    store->SetMesh(mesh::CreateBox());
    store->SetDepth(0.1f);
    store->AddComponent(new Collision(box_));
    store->AddComponent(new Status(ObjectType::Door));
    store->AddComponent(new Sprite("asset/images/door.png"));

    room2 = new Object();
    room2->SetTranslation({ 500,0 });
    room2->SetScale({ 50.f });
    room2->SetMesh(mesh::CreateBox());
    room2->SetDepth(0.1f);
    room2->AddComponent(new Collision(box_));
    room2->AddComponent(new Status(ObjectType::Door));
    room2->AddComponent(new Sprite("asset/images/door.png"));


    room = new Object();
    room->SetTranslation({ -500,0 });
    room->SetScale({ 50.f });
    room->SetMesh(mesh::CreateBox());
    room->SetDepth(0.1f);
    room->AddComponent(new Collision(box_));
    room->AddComponent(new Status(ObjectType::Door));
    room->AddComponent(new Sprite("asset/images/door.png"));

    enemy = new Object();
    enemy->SetTranslation({ -250, 250 });
    enemy->SetScale({ 50 });
    enemy->SetMesh(mesh::CreateBox());
    enemy->AddComponent(new Enemy(MoveType::straight));
    enemy->AddComponent(new RigidBody());
    enemy->AddComponent(new Collision());
    enemy->AddComponent(new Status(ObjectType::Enemy));
    enemy->AddComponent(new Animation("asset/images/Enemies/2_Left.png", "right", 4, 0.2f, true));
    enemy->GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/Enemies/2_Right.png", "left", 4, 0.2f, true);

    GetPlayerPointer()->SetTranslation(-StateManager_.player_position);

    Objectmanager_.AddObject(enemy);
    Objectmanager_.AddObject(room);
    Objectmanager_.AddObject(room2);
    Objectmanager_.AddObject(store);
    Objectmanager_.AddObject(background);
}

void Room1::Update(float dt)
{
    if (Input::IsKeyTriggered(GLFW_KEY_Q) && store->GetComponentByTemplate<Collision>()->GetIsDoor())
    {
        StateManager_.player_position = GetPlayerPointer()->GetTransform().GetTranslation();
        ChangeLevel("Store");
    }
    if (Input::IsKeyTriggered(GLFW_KEY_Q) && room2->GetComponentByTemplate<Collision>()->GetIsDoor())
    {
        StateManager_.player_position = GetPlayerPointer()->GetTransform().GetTranslation();
        ChangeLevel("Room2");
    }
    if (Input::IsKeyTriggered(GLFW_KEY_Q) && room->GetComponentByTemplate<Collision>()->GetIsDoor())
    {
        StateManager_.player_position = GetPlayerPointer()->GetTransform().GetTranslation();
        ChangeLevel("remake");
    }

    enemy->GetComponentByTemplate<Enemy>()->Move(GetPlayerPointer()->GetTransform().GetTranslation());

    if (enemy->GetComponentByTemplate<RigidBody>()->GetVelocity().x < 0)
    {
        enemy->GetComponentByTemplate<Animation>()->ChangeAnimation("right", "left");
    }
    else
        enemy->GetComponentByTemplate<Animation>()->ChangeAnimation("left", "right");
}

void Room1::ShutDown()
{
    UnLoad();
}
