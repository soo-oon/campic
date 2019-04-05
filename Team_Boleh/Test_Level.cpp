#include "Test_Level.hpp"
#include "Capture.hpp"
#include "Projectile.hpp"

void Test_Level::Initialize()
{
	Object* temp = new Object();
	temp->SetTranslation({ -600,-230 });
	temp->SetScale({ 50.0f, 50.0f });
	temp->SetMesh(mesh::CreateBox(1, { 255,255,255, 255 }));
	temp->SetDepth(-0.5f);
	temp->SetObjectType(ObjectType::Player);
	temp->AddInitComponent(new RigidBody());
	temp->AddInitComponent(new Collision(box_));
	temp->AddInitComponent(new Animation("asset/images/Enemies/1_Right.png", "player", 5, 0.2f, true));
	SetStartPosition(temp->GetTransform().GetTranslation());

	Object* player_camera = new Object();
	player_camera->SetScale({ 300.0f, 175.0f });
	player_camera->SetDepth(0.8f);
	player_camera->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	player_camera->SetObjectType(ObjectType::None);
	player_camera->AddComponent(new Animation("asset/images/camera_frame.png", "basic_camera", 2, 0.5, true));
	player_camera->GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/cheese.png", "cheese", 2, 0.5, true);
	player_camera->AddComponent(new Capture(GetStartPosition()));

	Object* camera = new Object();
	camera->SetObjectType(ObjectType::Camera);
	camera->AddComponent(new Camera("Test_Level"));


	Object* cannon = new Object();
	cannon->SetTranslation({ 480,-150 });
	cannon->SetScale({ 150,150 });
	cannon->SetObjectType(ObjectType::Item_Static);
	cannon->SetMesh(mesh::CreateBox());
	cannon->AddComponent(new Collision(box_));
	cannon->AddComponent(new Animation("asset/images/cannon.png", "cannon_standing", 5, 0.4f, true));
	cannon->GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/cannon_fire.png", "cannon_fire", 6, 0.1, false);
	cannon->AddComponent(new Projectile(4.0f, 10.0f, Projectile_Type::Cannon));
	cannon->GetComponentByTemplate<Projectile>()->SetFireDir({ 350, 0 });

	Object* weapon = new Object();
	weapon->SetTranslation({ 30 , -235 });
	weapon->SetScale({ 100, 50 });
	weapon->SetObjectType(ObjectType::Item_Dynamic);
	weapon->SetMesh(mesh::CreateBox());
	weapon->AddComponent(new Sprite("asset/images/weapon.png"));
	weapon->AddComponent(new Collision(box_));
	weapon->AddComponent(new Projectile(1.0f, 3.0f, Projectile_Type::Weapon));
	weapon->GetComponentByTemplate<Projectile>()->SetFireDir({ 1000, 0 });

	Object* test1 = new Object();
	test1->SetTranslation({ 0, 400 });
	test1->SetScale({ 50, 50 });
	test1->SetObjectType(ObjectType::None);
	test1->SetMesh(mesh::CreateBox(1, Colors::Blue));
	test1->AddComponent(new RigidBody());
	test1->AddComponent(new Collision());

	Object* test2 = new Object();
	test2->SetTranslation({ 100, 400 });
	test2->SetScale({ 50, 50 });
	test2->SetObjectType(ObjectType::None);
	test2->SetMesh(mesh::CreateBox(1, Colors::Red));
	test2->AddComponent(new RigidBody());
	test2->AddComponent(new Collision());

	obj.push_back(temp);
	obj.push_back(camera);
	obj.push_back(player_camera);
	//obj.push_back(cannon);
	//obj.push_back(weapon);
	obj.push_back(test1);
	obj.push_back(test2);


	for (auto i : obj)
	{
		Objectmanager_.AddObject(i);
	}
}

void Test_Level::Update(float dt)
{
}

void Test_Level::ShutDown()
{
}
