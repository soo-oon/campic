#include "Room2.hpp"
#include "Application.hpp"
#include "Status.hpp"
#include "Enemy.hpp"
#include <iostream>


void Room2::Initialize()
{
    int w, h;
    glfwGetWindowSize(Application_.GetWindow(), &w, &h);

    Object * background = new Object();
    background->SetTranslation({ 0,0 });
    background->SetScale(vector2(static_cast<float>(w), static_cast<float>(h)));
    background->SetMesh(mesh::CreateBox(1, {100,255,100}));
    background->SetDepth(0.9f);
    background->AddComponent(new Sprite("asset/images/background1.png"));
    //background.GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/UI/Menu_background.png");

    room1 = new Object();
    room1->SetTranslation({ -500,0 });
    room1->SetScale({ 50.f });
    room1->SetMesh(mesh::CreateBox());
    room1->SetDepth(0.1f);
    room1->AddComponent(new Collision(box_));
    room1->AddComponent(new Status(ObjectType::Door));
    room1->AddComponent(new Sprite("asset/images/door.png"));


    boss_room = new Object();
    boss_room->SetTranslation({ 500,0 });
    boss_room->SetScale({ 50.f });
    boss_room->SetMesh(mesh::CreateBox());
    boss_room->SetDepth(0.1f);
    boss_room->AddComponent(new Collision(box_));
    boss_room->AddComponent(new Status(ObjectType::Door));
    boss_room->AddComponent(new Sprite("asset/images/door.png"));

    enemy = new Object();
    enemy->SetTranslation({ -250, 250 });
    enemy->SetScale({ 50 });
    enemy->SetMesh(mesh::CreateBox());
    enemy->AddComponent(new RigidBody());
    enemy->AddComponent(new Collision());
    enemy->AddComponent(new Status(ObjectType::Enemy,5,1,1.5));
    enemy->AddComponent(new Enemy(MoveType::straight, GetPlayerPointer()));
    enemy->AddComponent(new Animation("asset/images/Enemies/3_Left.png", "right", 4, 0.2f, true));
    enemy->GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/Enemies/3_Right.png", "left", 4, 0.2f, true);


    Object* enemy1 = new Object();
    enemy1->SetTranslation({ 250, 250 });
    enemy1->SetScale({ 50 });
    enemy1->SetMesh(mesh::CreateBox());
    enemy1->AddComponent(new RigidBody());
    enemy1->AddComponent(new Collision());
    enemy1->AddComponent(new Status(ObjectType::Enemy, 5, 1, 1.5));
    enemy1->AddComponent(new Enemy(MoveType::straight, GetPlayerPointer()));
    enemy1->AddComponent(new Animation("asset/images/Enemies/3_Left.png", "right", 4, 0.2f, true));
    enemy1->GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/Enemies/3_Right.png", "left", 4, 0.2f, true);


     Object* enemy2 = new Object();
    enemy2->SetTranslation({ -250, -250 });
    enemy2->SetScale({ 50 });
    enemy2->SetMesh(mesh::CreateBox());
    enemy2->AddComponent(new RigidBody());
    enemy2->AddComponent(new Collision());
    enemy2->AddComponent(new Status(ObjectType::Enemy, 5, 1, 1.5));
    enemy2->AddComponent(new Enemy(MoveType::straight, GetPlayerPointer()));
    enemy2->AddComponent(new Animation("asset/images/Enemies/3_Left.png", "right", 4, 0.2f, true));
    enemy2->GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/Enemies/3_Right.png", "left", 4, 0.2f, true);
    GetPlayerPointer()->SetTranslation(-StateManager_.player_position);



    Objectmanager_.AddObject(room1);
    Objectmanager_.AddObject(enemy);
    Objectmanager_.AddObject(enemy1);
    Objectmanager_.AddObject(enemy2);
    Objectmanager_.AddObject(boss_room);
    Objectmanager_.AddObject(background);
}

void Room2::Update(float dt)
{
	if (enemy->GetComponentByTemplate<Status>()->IsAlive())
		std::cout << "live" << std::endl;
	else
		std::cout << "die" << std::endl;

    if (Input::IsKeyTriggered(GLFW_KEY_Q) && room1->GetComponentByTemplate<Collision>()->GetIsDoor())
    {
        StateManager_.player_position = GetPlayerPointer()->GetTransform().GetTranslation();
        ChangeLevel("Room1");
    }
    if (Input::IsKeyTriggered(GLFW_KEY_Q) && boss_room->GetComponentByTemplate<Collision>()->GetIsDoor())
    {
        StateManager_.player_position = GetPlayerPointer()->GetTransform().GetTranslation();
        ChangeLevel("Boss");
    }

}

void Room2::ShutDown()
{
    UnLoad();
}
