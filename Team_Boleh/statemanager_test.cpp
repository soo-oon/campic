#include "statemanager_test.hpp"
#include "Input.hpp"
#include "Sprite.hpp"
#include "Collision.hpp"
#include "Camera.hpp"
#include "Animation.hpp"
#include <iostream>
#include "Character.hpp"
#include "Player.hpp"
#include "status.hpp"
#include "Card.hpp"

void test_statemanager::Initialize()
{
	GetObjectManager()->AddObject("camera");
	GetSoundMap()->AddSound("asset/sounds/inchant.mp3");
	GetSoundMap()->AddSound("asset/sounds/punch.wav");

	GetObjectManager()->FindObject("camera")->SetScale({ 10,10 });
	GetObjectManager()->FindObject("camera")->SetTranslation({ 0,0 });

	GetObjectManager()->FindObject("camera")->AddComponent(new Camera(this));

	player = GetObjectManager()->FindObject("Player").get();

	background = BuildAndRegisterDynamicObject("background", vector2(0, 0), vector2());
	background->SetDepth(0.99f);
	background->AddComponent(new Sprite());
	background->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/background.png");

	sword = GetObjectManager()->FindObject("Sword").get();

	spade = BuildAndRegisterDynamicObject("spade", vector2(350, -100), vector2(25.f, 25.f));
	spade->AddComponent(new Sprite());
	spade->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/spade.png");
	spade->AddComponent(new RigidBody());
	spade->GetMesh().Invisible();

	spade1 = BuildAndRegisterDynamicObject("spade1", vector2(420, -100), vector2(50.f, 50.f));
	spade1->AddComponent(new Sprite());
	spade1->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/spade.png");
	spade1->AddComponent(new Collision(box_, {}, { 50.0f, 50.0f }));
	spade1->GetComponentByTemplate<Collision>()->SetRestitutionType(RestitutionType::none);
	spade1->AddComponent(new Character(ObjectType::card));
	spade1->AddComponent(new Card("spade"));


	boss = BuildAndRegisterDynamicObject("boss", { 300.f,-150.f }, { 200.f,200.f });
	boss->AddComponent(new Animation("asset/images/boss.png", "boss", 5, 0.2f));
	boss->AddComponent(new Collision(box_, {}, {boss->GetTransform().GetScale()}));
	boss->AddComponent(new RigidBody());
	boss->GetComponentByTemplate<Collision>()->SetRestitutionType(RestitutionType::none);
	boss->AddComponent(new Character(ObjectType::opponent));
	boss->AddComponent(new Status(20, 1, 1.5f));

	door = BuildAndRegisterDynamicObject("door", vector2(500, 0), vector2(75.f, 75.f));
	door->AddComponent(new Sprite());
	door->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/hero.png");
	door->AddComponent(new Collision(box_, {}, { 75.0f, 75.0f }));
	door->GetComponentByTemplate<Collision>()->SetRestitutionType(RestitutionType::none);
	door->AddComponent(new Character(ObjectType::door));

	clover = BuildAndRegisterDynamicObject("clover", vector2(350, 100), vector2(25.f, 25.f));
	clover->AddComponent(new Sprite());
	clover->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/clover.png");
	clover->AddComponent(new Character(ObjectType::none));
	clover->AddComponent(new RigidBody());
	clover->GetMesh().Invisible();

	clover1 = BuildAndRegisterDynamicObject("clover1", vector2(420, 100), vector2(50.f, 50.f));
	clover1->AddComponent(new Sprite());
	clover1->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/clover.png");
	clover1->AddComponent(new Collision(box_, {}, { 50.0f, 50.0f }));
	clover1->GetComponentByTemplate<Collision>()->SetRestitutionType(RestitutionType::stop);
	clover1->AddComponent(new Character(ObjectType::card));
	clover1->AddComponent(new Card("clover"));

	spark = BuildAndRegisterDynamicObject("spark", vector2(200, 0), vector2(100.f, 100.f));
	spark->AddComponent(new Animation("asset/images/sprite.png", "spark", 7, 0.08f));
	spark->GetMesh().Invisible();

}

void test_statemanager::Update(float dt)
{
	Camera* temp_camera = GetObjectManager()->FindObject("camera")->GetComponentByTemplate<Camera>();

	if (Input::IsKeyTriggered(GLFW_KEY_R))
		ChangeLevel("test");

	if (Input::IsKeyTriggered(GLFW_KEY_1))
		ChangeLevel("example");
	if (Input::IsKeyTriggered(GLFW_KEY_3))
		ChangeLevel("MapEditorTest");
	if (Input::IsKeyTriggered(GLFW_KEY_4))
		ChangeLevel("Particle");

	GetObjectManager()->FindObject("background")->SetScale(GetStateScreenSize());
	if (Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
	{
		GetSoundMap()->Play("asset/sounds/punch.wav");
	}
	if (Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
	{
		GetSoundMap()->Play("asset/sounds/punch.wav");
	}

	if(boss->GetComponentByTemplate<Collision>() != nullptr)
		BossMovement(boss, player, 20);

	if (Input::IsKeyTriggered(GLFW_KEY_T))
	{
		for (auto& i : player->GetComponentByTemplate<Player>()->GetCardList())
		{
			find(i);
		}
		if (card_list.size() > 1)
		{
			change_sword = true;
			GetSoundMap()->Play("asset/sounds/inchant.mp3");
			player->GetComponentByTemplate<Player>()->ClearCardList();
		}
	}
	spark->GetTransform().SetTranslation(vector2(sword->GetTransform().GetTranslation().x, sword->GetTransform().GetTranslation().y));
	if (change_sword)
	{
		Enchanted(sword, spark, card_list.at(0), card_list.at(1), dt);
	}
}

void test_statemanager::ShutDown()
{
	UnLoad();
}

Object* test_statemanager::BuildAndRegisterStaticObject(std::string object_name, vector2 position, vector2 scale)
{
	GetObjectManager()->AddObject(object_name);
	GetObjectManager()->FindObject(object_name)->SetScale(scale);
	GetObjectManager()->FindObject(object_name)->SetTranslation(position);
	GetObjectManager()->FindObject(object_name)->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));

	//trans form texture, 
	return GetObjectManager()->FindObject(object_name).get();
}
Object* test_statemanager::BuildAndRegisterDynamicObject(std::string object_name, vector2 position, vector2 scale)
{
	GetObjectManager()->AddObject(object_name);
	GetObjectManager()->FindObject(object_name)->SetScale(scale);
	GetObjectManager()->FindObject(object_name)->SetTranslation(position);
	GetObjectManager()->FindObject(object_name)->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	//GetObjectManager()->FindObject(object_name)->AddComponent(new Sprite());
	GetObjectManager()->FindObject(object_name)->AddComponent(new RigidBody());
	//trans form texture, 
	return GetObjectManager()->FindObject(object_name).get();
}
void test_statemanager::Attact(Object * object)
{
	if (Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
		object->GetComponentByTemplate<Collision>()->ToggleIsDamaged();
}
void test_statemanager::snailoption(Object * effect, Object* knife, float angle, float& angle_)
{
	float x_vel, y_vel;
	angle_ += angle;
	//card_velo -= 0.5f;
	if (dt_sum < 2)
		far *= 1.005f;
	else
		far *= 0.995f;
	x_vel = cos(angle_)*(card_velo)+sin(angle_)*(card_velo);
	y_vel = -sin(angle_)*(card_velo)+cos(angle_)*(card_velo);
	effect->GetTransform().SetTranslation(vector2(knife->GetTransform().GetTranslation().x - far * x_vel, knife->GetTransform().GetTranslation().y - far * y_vel));
	if (knife->GetTransform().GetTranslation().y > effect->GetTransform().GetTranslation().y)
	{
		effect->GetTransform().SetDepth(0.95f);
	}
	else
		effect->GetTransform().SetDepth(0.98f);
}
void test_statemanager::Enchanted(Object * sword, Object* effect, Object * card1, Object * card2, float dt)
{
	float big = 0;
	snailoption(card1, sword, -0.02f, rota_angle);
	snailoption(card2, sword, 0.02f, rota_angle1);

	if (dt_sum < 4)
	{
		dt_sum += dt;
		if (!card1->GetMesh().IsVisible() && !card2->GetMesh().IsVisible())
		{
			card1->GetMesh().Visible();
			card2->GetMesh().Visible();
		}
		if (dt_sum < 2)
			big = 1.01f;
		else
			big = 0.99f;
	}
	else if (card1->GetMesh().IsVisible() && card2->GetMesh().IsVisible())
	{
		card1->GetMesh().Invisible();
		card2->GetMesh().Invisible();
	}
	else
	{
		if (dt_sum < 7)
		{
			dt_sum += dt;
			if (!effect->GetMesh().IsVisible())
				effect->GetMesh().Visible();
		}
		else if (effect->GetMesh().IsVisible())
		{
			effect->GetMesh().Invisible();
			sword->GetTransform().SetScale(vector2(200.f, 150.f));
			sword->GetComponentByTemplate<Collision>()->ChangeCollisionBoxScale(vector2(150.f, 150.0f));
			sword->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/ice_sword.png");
			card_list.clear();
			change_sword = false;
		}
	}
	card1->GetTransform().SetScale(card1->GetTransform().GetScale()* big);
	card2->GetTransform().SetScale(card2->GetTransform().GetScale()* big);
}

void test_statemanager::SwordSwing(vector2 mouse_position, Object* player, Object* sword)
{
	vector2 swing_direction = normalize(vector2(mouse_position.x - player->GetTransform().GetTranslation().x,
		mouse_position.y - player->GetTransform().GetTranslation().y));
	sword->SetTranslation(vector2(
		player->GetTransform().GetTranslation().x + swing_direction.x *player->GetTransform().GetScale().x,
		player->GetTransform().GetTranslation().y + swing_direction.y *player->GetTransform().GetScale().y));
	float anglerad = atan2(mouse_position.y - player->GetTransform().GetTranslation().y, mouse_position.x - player->GetTransform().GetTranslation().x);
	float angledeg = (180 / 3.14f)* anglerad;
	sword->SetRotation(angledeg - 90);
}
void test_statemanager::PlayerSwing(vector2 mouse_position, Object * player)
{
	vector2 swing_direction = normalize(vector2(mouse_position.x - player->GetTransform().GetTranslation().x,
		mouse_position.y - player->GetTransform().GetTranslation().y));
	float anglerad = atan2(mouse_position.y - player->GetTransform().GetTranslation().y, mouse_position.x - player->GetTransform().GetTranslation().x);
	float angledeg = (180 / 3.14f)* anglerad;
	player->SetRotation(angledeg -270);
}

void test_statemanager::find(std::string card_)
{
	card_list.push_back(GetObjectManager()->FindObject(card_).get());
}

void test_statemanager::BossMovement(Object * boss_monster, Object* player, float dt)
{
	vector2 come = vector2(player->GetTransform().GetTranslation().x - boss_monster->GetTransform().GetTranslation().x,
		player->GetTransform().GetTranslation().y - boss_monster->GetTransform().GetTranslation().y);
	vector2 no_come = normalize(come);
	if (magnitude(come) < magnitude(boss_monster->GetTransform().GetScale()))
	{
		boss_monster->GetComponentByTemplate<RigidBody>()->SetVelocity(0);
	}
	else
		boss_monster->GetComponentByTemplate<RigidBody>()->SetVelocity(dt* no_come);
		
}
