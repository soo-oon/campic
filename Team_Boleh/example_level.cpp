#include "example_level.hpp"
#include <iostream>
#include "Sprite.hpp"
#include "PhysicsComponent.hpp"
#include "Input.hpp"
#include "WorldPhysics.h"
#include "Animation.hpp"
#include "Collision.hpp"

bool example::Initialize()
{
    objectmanager->AddObject("test");
    check = objectmanager->FindObject("test");
    objectmanager->AddObject("player");
    player = objectmanager->FindObject("player");

    player->SetScale({ 200.0f, 150.0f });
    player->SetTranslation({ 0,0 });
    player->GetTransform().SetRotation(50);
    player->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));

    player->AddComponent(new Animation(4, 0.5, "asset/animation_strange.png"));
    player->AddComponent(new Physics());
    player->AddComponent(new Collision());

	check->SetScale({ 200.0f, 150.0f });
	check->SetTranslation({ 150,0 });
	check->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));

	check->AddComponent(new Animation(4, 0.5, "asset/animation_strange.png"));
	check->AddComponent(new Physics());
        player->AddComponent(new Collision());

	//check->AddComponent(new Sprite());
	//check->GetComponentByTemplate<Sprite>()->Texture_Load("asset/animation_strange.png");
	//check->GetComponentByTemplate<Sprite>()->Texture_Load("asset/strange_for_A.png");

    return true;
}

void example::Update(float dt)
{
    opponent.clear();
    for (size_t i = 0 ; i < player->GetMesh().GetPointCount(); i++)
        opponent.emplace_back(player->GetTransform().GetTRS()*static_cast<vector2>(player->GetMesh().GetPoint(i)));

    mesh_p.clear();
    for (size_t i = 0; i < check->GetMesh().GetPointCount(); i++)
    {
        mesh_p.emplace_back( check->GetTransform().GetTRS()*static_cast<vector2>(check->GetMesh().GetPoint(i)));
        std::cout << mesh_p[i].x << ", " << mesh_p[i].y << std::endl;
        //std::cout << check->GetTransform().GetTranslation().x << ", " << check->GetTransform().GetTranslation().y << std::endl;
    }
    player->GetComponentByTemplate<Collision>()->intersection_check(mesh_p, opponent);
	world_physics->Movement_by_key(*check);
	//world_physics->Movement(*check);
	check->GetComponentByTemplate<Physics>()->Update(dt);
	check->SetTranslation(check->GetComponentByTemplate<Physics>()->GetPosition());
	//check->GetComponentByTemplate<Animation>()->Update(dt);

	//std::cout << check->GetComponentByTemplate<Physics>()->GetPosition().x << ", " << check->GetComponentByTemplate<Physics>()->GetPosition().y << std::endl;
}

void example::ShutDown()
{
}

vector2 multi_plus(Object *ob, size_t i)
{
    float x_ = (static_cast<vector2>(ob->GetMesh().GetPoint(i)).x * ob->GetTransform().GetScale().x) + ob->GetTransform().GetTranslation().x;
    float y_ = (static_cast<vector2>(ob->GetMesh().GetPoint(i)).y * ob->GetTransform().GetScale().y) + ob->GetTransform().GetTranslation().y;
    return (x_,y_);
}
