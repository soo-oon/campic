/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:  level2.cpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Jun Soon Woo
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

#include "level2.hpp"
#include "Input.hpp"
#include "Animation.hpp"
#include <iostream>
#include "Status.hpp"
#include "Particle_Generator.hpp"
#include "Card.hpp"

void level2::Initialize()
{
	Object temp;

	temp.SetTranslation({ 100,-150 });
	temp.SetScale({ 50.0f, 50.0f });
	temp.SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
        temp.AddComponent(new RigidBody());
	temp.AddComponent(new Sprite("asset/images/Dr_Strange.png"));
	temp.AddComponent(new Collision(box_, {}, { 100.0f, 100.0f }));
	temp.AddComponent(new Status(ObjectType::Enemy ,5, 0, 1.f));
	temp.AddComponent(new Particle_Generator(100, 2.0f, 5, { 0,0 }, { 3,3 }));

	Objectmanager_.AddObject(temp);

        Object card, card1;

        card.SetTranslation({ 300,300 });
        card.SetScale({ 30.f,30.f });
        card.SetMesh(mesh::CreateBox(1,{255,0,0}));
        card.AddComponent(new Card("Red"));
        card.AddComponent(new Collision(box_,{0,0},{30.f,30.f}));
        card.AddComponent(new Status(ObjectType::Item));

        card1.SetTranslation({ 250,-250 });
        card1.SetScale({ 30.f,30.f });
        card1.SetMesh(mesh::CreateBox(1,{0,255,0}));
        card1.AddComponent(new Card("Blue"));
        card1.AddComponent(new Collision(box_, { 0,0 }, { 30.f,30.f }));
        card1.AddComponent(new Status(ObjectType::Item));
        Objectmanager_.AddObject(card);
        Objectmanager_.AddObject(card1);

        //Objectmanager_.GetObjectMap()[0]->AddComponent(new Particle_Generator(100, 1.0f, 5, { 0,0 }, { 3,3 }));

	//std::cout << Objectmanager_.GetObjectMap().size() << std::endl;
	//std::cout << "-------------" << std::endl;


	/*
	Object* player = new Object();
	player.SetTranslation({ 0,0 });
	player.SetScale({ 100.0f, 100.0f });
	player.SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	player.AddComponent(new RigidBody());
	player.AddComponent(new Animation("asset/images/Player.png", "player", 8, 0.05f));
	player.GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/attack.png", "attack", 4, 0.1f, false);
	player.AddComponent(new Collision(box_, {}, { 100.0f, 100.0f }));
	player.AddComponent(new Character(ObjectType::player));
	player.AddComponent(new Status(5, 1, 1.f));
	player->AddComponent(new Player());

	Objectmanager_.AddObject(*player);
	*/

    /*
	AudioManager_.LoadSong("asset/sounds/bgm.mp3");
	AudioManager_.LoadSFX("asset/sounds/punch.wav");
	AudioManager_.PlaySong("asset/sounds/bgm.mp3");
	
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
	boss->AddComponent(new Status(100, 1, 1.5f));

	door = BuildAndRegisterDynamicObject("door", vector2(500, 0), vector2(75.f, 75.f));
	door->AddComponent(new Sprite());
	door->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/hero.png");
	door->AddComponent(new Collision(box_, {}, { 75.0f, 75.0f }));
	door->GetComponentByTemplate<Collision>()->SetRestitutionType(RestitutionType::none);
	door->AddComponent(new Character(ObjectType::door));

	heart = BuildAndRegisterDynamicObject("heart", vector2(350, 100), vector2(25.f, 25.f));
	heart->AddComponent(new Sprite());
	heart->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/heart.png");
	heart->AddComponent(new Character(ObjectType::none));
	heart->AddComponent(new RigidBody());
	heart->GetMesh().Invisible();

	dia = BuildAndRegisterDynamicObject("dia", vector2(350, -100), vector2(25.f, 25.f));
	dia->AddComponent(new Sprite());
	dia->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/dia.png");
	dia->AddComponent(new Character(ObjectType::none));
	dia->AddComponent(new RigidBody());
	dia->GetMesh().Invisible();

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
    */
}

void level2::Update(float dt)
{
	if (Input::IsKeyTriggered(GLFW_KEY_R))
	{
		ChangeLevel("remake");
	}

	if (Input::IsKeyTriggered(GLFW_KEY_F1))
	{
		for (auto& obj : Objectmanager_.GetObjectMap())
		{
			JSON_.ObjectsToDocument(obj.get());
		}
		JSON_.GetObjectDocument().SetObject();
		std::cout << "Objects Saved" << std::endl;
	}

	if (Input::IsKeyTriggered(GLFW_KEY_F2))
	{
		/*for (auto& obj : Objectmanager_.GetObjectMap())
		{
			JSON_.ObjectsToDocument(obj.get());
		}*/
		JSON_.LoadObjectFromJson();
		//JSON_.GetObjectDocument().SetObject();
		std::cout << "Objects Loaded" << std::endl;
	}

	if (Input::IsKeyTriggered(GLFW_KEY_SPACE))
	{
		for(auto& obj : Objectmanager_.GetObjectMap())
		{
			if(auto temp = obj.get()->GetComponentByTemplate<Status>(); temp->GetObjectType()!= ObjectType::Player)
			{
				temp->Damaged(5);
			}
		}
	}

	/*if (Input::IsKeyTriggered(GLFW_KEY_Q) && door->GetComponentByTemplate<Collision>()->GetIsDoor())
		ChangeLevel("StartMenu");

	if (!player->GetComponentByTemplate<Status>()->GetLived())
		ChangeLevel("StartMenu");


	if (Input::IsKeyTriggered(GLFW_KEY_C))
	{
		shot_char++;
		Shot(shot_string + std::to_string(shot_char));
	}

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

	if (Input::IsKeyTriggered(GLFW_KEY_E))
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
	}*/
}

void level2::ShutDown()
{
	UnLoad();
}
/*
Object* level2::BuildAndRegisterStaticObject(std::string object_name, vector2 position, vector2 scale)
{
	GetObjectManager()->AddObject(object_name);
	GetObjectManager()->FindObject(object_name)->SetScale(scale);
	GetObjectManager()->FindObject(object_name)->SetTranslation(position);
	GetObjectManager()->FindObject(object_name)->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));

	//trans form texture, 
	return GetObjectManager()->FindObject(object_name).get();
}
Object* level2::BuildAndRegisterDynamicObject(std::string object_name, vector2 position, vector2 scale)
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
void level2::Attact(Object * object)
{
	if (Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
		object->GetComponentByTemplate<Collision>()->ToggleIsDamaged();
}
void level2::snailoption(Object * effect, Object* knife, float angle, float& angle_)
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
void level2::Enchanted(Object * sword, Object* effect, Object * card1, Object * card2, float dt)
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
			sword->GetComponentByTemplate<Sword>()->SetName("ice_sword");
			card_list.clear();
			change_sword = false;
			dt_sum = 0; rota_angle = 0; rota_angle1 = 0; far = 1;
		}
	}
	card1->GetTransform().SetScale(card1->GetTransform().GetScale()* big);
	card2->GetTransform().SetScale(card2->GetTransform().GetScale()* big);
}

void level2::SwordSwing(vector2 mouse_position, Object* player, Object* sword)
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
void level2::PlayerSwing(vector2 mouse_position, Object * player)
{
	vector2 swing_direction = normalize(vector2(mouse_position.x - player->GetTransform().GetTranslation().x,
		mouse_position.y - player->GetTransform().GetTranslation().y));
	float anglerad = atan2(mouse_position.y - player->GetTransform().GetTranslation().y, mouse_position.x - player->GetTransform().GetTranslation().x);
	float angledeg = (180 / 3.14f)* anglerad;
	player->SetRotation(angledeg -270);
}

void level2::find(std::string card_)
{
	card_list.push_back(GetObjectManager()->FindObject(card_).get());
}

void level2::BossMovement(Object * boss_monster, Object* player, float dt)
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

void level2::Shot(std::string name)
{
	GetObjectManager()->AddObject(name);
	GetObjectManager()->FindObject(name)->AddComponent(new FireBall(player, sword, 5.0f));
}
*/
