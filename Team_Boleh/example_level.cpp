#include "example_level.hpp"
#include <iostream>
#include "Sprite.hpp"
#include "RigidBody.hpp"
#include "Input.hpp"
#include "Animation.hpp"
#include "Collision.hpp"
#include "vector2.hpp"
#include "Character.hpp"
#include <limits.h>
#include "Player.hpp"
#include "status.hpp"
#include "Card.hpp"
#include "Sword.hpp"
#include "Graphics.hpp"


void example::Initialize()
{
	//Load();

	GetSoundMap()->AddSound("asset/sounds/inchant.mp3");
	GetSoundMap()->AddSound("asset/sounds/punch.wav");

	player = GetObjectManager()->FindObject("Player").get();

	GetObjectManager()->AddObject("camera");

	GetObjectManager()->FindObject("camera")->SetScale({ 10,10 });
	GetObjectManager()->FindObject("camera")->SetTranslation({ 0,0 });
	GetObjectManager()->FindObject("camera")->AddComponent(new Camera(this));

	slime = BuildAndRegisterDynamicObject("slime", vector2(-300, -300), vector2(75.f, 75.f));
	slime->AddComponent(new Animation("asset/images/slime.png", "slime", 6, 0.25));
	slime->AddComponent(new RigidBody());
	slime->AddComponent(new Collision(box_, {}, {75.0f, 75.0f}));
	slime->GetComponentByTemplate<Collision>()->SetRestitutionType(RestitutionType::stop);
	slime->AddComponent(new Character(ObjectType::opponent));
	slime->AddComponent(new Status(5, 1, 1.f));


	scol = BuildAndRegisterDynamicObject("scol", vector2(-300, 300), vector2(75.f, 75.f));
	scol->AddComponent(new Animation("asset/images/scol.png", "scol", 6, 0.25));
	scol->AddComponent(new RigidBody());
	scol->AddComponent(new Collision(box_, {}, { 75.0f, 75.0f }));
	scol->GetComponentByTemplate<Collision>()->SetRestitutionType(RestitutionType::stop);
	scol->AddComponent(new Character(ObjectType::opponent));
	scol->AddComponent(new Status(5, 1, 1.f));

	opponent1 = BuildAndRegisterDynamicObject("opponent1", vector2(-300,0), vector2(75.f, 75.f));
	opponent1->AddComponent(new Animation("asset/images/scol.png", "scol", 6, 0.25));
	opponent1->AddComponent(new RigidBody());
	opponent1->AddComponent(new Collision(box_, {}, { 75.0f, 75.0f }));
	opponent1->GetComponentByTemplate<Collision>()->SetRestitutionType(RestitutionType::stop);
	opponent1->AddComponent(new Character(ObjectType::opponent));
	opponent1->AddComponent(new Status(5, 1, 1.f));

	opponent2 = BuildAndRegisterDynamicObject("opponent2", vector2(200, -250), vector2(75.f, 75.f));
	opponent2->AddComponent(new Animation("asset/images/scol.png", "scol", 6, 0.25));
	opponent2->AddComponent(new RigidBody());
	opponent2->AddComponent(new Collision(box_, {}, { 75.0f, 75.0f }));
	opponent2->GetComponentByTemplate<Collision>()->SetRestitutionType(RestitutionType::stop);
	opponent2->AddComponent(new Character(ObjectType::opponent));
	opponent2->AddComponent(new Status(5, 1, 1.f));

	opponent3 = BuildAndRegisterDynamicObject("opponent3", vector2(0, 200), vector2(75.f, 75.f));
	opponent3->AddComponent(new Animation("asset/images/slime.png", "slime", 6, 0.25));
	opponent3->AddComponent(new RigidBody());
	opponent3->AddComponent(new Collision(box_, {}, { 75.0f, 75.0f }));
	opponent3->GetComponentByTemplate<Collision>()->SetRestitutionType(RestitutionType::stop);
	opponent3->AddComponent(new Character(ObjectType::opponent));
	opponent3->AddComponent(new Status(5, 1, 1.f));

	opponent4 = BuildAndRegisterDynamicObject("opponent4", vector2(300, 250), vector2(75.f, 75.f));
	opponent4->AddComponent(new Animation("asset/images/slime.png", "slime", 6, 0.25));
	opponent4->AddComponent(new RigidBody());
	opponent4->AddComponent(new Collision(box_, {}, { 75.0f, 75.0f }));
	opponent4->GetComponentByTemplate<Collision>()->SetRestitutionType(RestitutionType::stop);
	opponent4->AddComponent(new Character(ObjectType::opponent));
	opponent4->AddComponent(new Status(5, 1, 1.f));

        dia = BuildAndRegisterDynamicObject("dia", vector2(350, -100), vector2(25.f, 25.f));
        dia->AddComponent(new Sprite());
        dia->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/dia.png");
        dia->AddComponent(new Character(ObjectType::none));
	dia->AddComponent(new RigidBody());
	dia->GetMesh().Invisible();

	heart = BuildAndRegisterDynamicObject("heart", vector2(350, 100), vector2(25.f, 25.f));
	heart->AddComponent(new Sprite());
	heart->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/heart.png");
	heart->AddComponent(new Character(ObjectType::none));
	heart->AddComponent(new RigidBody());
	heart->GetMesh().Invisible();

	spade = BuildAndRegisterDynamicObject("spade", vector2(350, -100), vector2(25.f, 25.f));
	spade->AddComponent(new Sprite());
	spade->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/spade.png");
	spade->AddComponent(new RigidBody());
	spade->GetMesh().Invisible();

	clover = BuildAndRegisterDynamicObject("clover", vector2(350, 100), vector2(25.f, 25.f));
	clover->AddComponent(new Sprite());
	clover->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/clover.png");
	clover->AddComponent(new Character(ObjectType::none));
	clover->AddComponent(new RigidBody());
	clover->GetMesh().Invisible();


	dia1 = BuildAndRegisterDynamicObject("dia1", vector2(420, -100), vector2(50.f, 50.f));
	dia1->AddComponent(new Sprite());
	dia1->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/dia.png");
	dia1->AddComponent(new Collision(box_, {}, {50.0f, 50.0f}));
	dia1->GetComponentByTemplate<Collision>()->SetRestitutionType(RestitutionType::none);
    dia1->AddComponent(new Character(ObjectType::card));
    dia1->AddComponent(new Card("dia"));


	door = BuildAndRegisterDynamicObject("door", vector2(500, 0), vector2(75.f, 75.f));
	door->AddComponent(new Sprite());
	door->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/hero.png");
	door->AddComponent(new Collision(box_, {}, { 75.0f, 75.0f }));
	door->GetComponentByTemplate<Collision>()->SetRestitutionType(RestitutionType::none);
	door->AddComponent(new Character(ObjectType::door));

	heart1 = BuildAndRegisterDynamicObject("heart1", vector2(420, 100), vector2(50.f, 50.f));
	heart1->AddComponent(new Sprite());
	heart1->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/heart.png");
	heart1->AddComponent(new Collision(box_, {}, {50.0f, 50.0f}));
	heart1->GetComponentByTemplate<Collision>()->SetRestitutionType(RestitutionType::stop);
	heart1->AddComponent(new Character(ObjectType::card));
	heart1->AddComponent(new Card("heart"));

	sword = GetObjectManager()->FindObject("Sword").get();

	spark = BuildAndRegisterDynamicObject("spark", vector2(200, 0), vector2(100.f, 100.f));
	spark->AddComponent(new Animation("asset/images/sprite.png", "spark", 7, 0.08f));
	spark->GetMesh().Invisible();
		
	background = BuildAndRegisterDynamicObject("background", vector2(0,0), vector2(150.f, 150.f));
	background->SetDepth(0.99f);
	background->AddComponent(new Sprite());
	background->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/background.png");

}

void example::Update(float dt)
{
	if (!player->GetComponentByTemplate<Status>()->GetLived())
		ChangeLevel("StartMenu");


        if (Input::IsKeyTriggered(GLFW_KEY_E))
        {
			if(!change_sword)
			{ 
		card_list.clear();
		for(auto& i : player->GetComponentByTemplate<Player>()->GetCardList())
		{
			find(i);
		}
		if (card_list.size() > 1)
		{
			change_sword = true;
			MakeManyEffect("dia");
			GetSoundMap()->Play("asset/sounds/inchant.mp3");
			player->GetComponentByTemplate<Player>()->ClearCardList();
		}
		}
        }
	spark->GetTransform().SetTranslation(vector2(sword->GetTransform().GetTranslation().x, sword->GetTransform().GetTranslation().y));
	if(change_sword)
	{
		Enchanted(sword, spark, card_list.at(0), card_list.at(1), dt);
	}
	for (auto i : dump)
	{
		if (change_sword)
		{
			if (i->GetComponentByTemplate<Collision>() != nullptr)
				ComePlayer(player, i, 100);
		}
	}
	if (Input::IsKeyTriggered(GLFW_KEY_R))
		ChangeLevel("example");
	if (Input::IsKeyTriggered(GLFW_KEY_2))
		ChangeLevel("test");
	if (Input::IsKeyTriggered(GLFW_KEY_3))
		ChangeLevel("MapEditorTest");
	if (Input::IsKeyTriggered(GLFW_KEY_4))
		ChangeLevel("Particle");

	if (Input::IsKeyTriggered(GLFW_KEY_C))
	{
		shot_char++;
		Shot(shot_string + shot_char);
	}
        if (sword->GetComponentByTemplate<RigidBody>()->GetVelocity() != vector2(0, 0))
            sword->GetComponentByTemplate<RigidBody>()->SetVelocity(vector2(0, 0));

	if (Input::IsKeyTriggered(GLFW_KEY_X))
	{
		Power_shot();
	}

	if (isshot)
		dt_power_shot += dt;
	if(dt_power_shot > 3)
	std::cout << dt_power_shot << std::endl;

	if (dt_power_shot > 3)
	{
		GetObjectManager()->RemoveObject("power");
		isshot = false;
		dt_power_shot = 0;
	}

	if (Input::IsKeyTriggered(GLFW_KEY_Q) && door->GetComponentByTemplate<Collision>()->GetIsDoor())
		ChangeLevel("test");


	if(scol->GetComponentByTemplate<Status>() != nullptr)
	ForProtoType(player, scol, 20);
	if (slime->GetComponentByTemplate<Status>() != nullptr)
	ForProtoType(player, slime, 20);
	if (opponent1->GetComponentByTemplate<Status>() != nullptr)
	ForProtoType(player, opponent1, 20);
	if (opponent2->GetComponentByTemplate<Status>() != nullptr)
	ForProtoType(player, opponent2, 20);
	if (opponent3->GetComponentByTemplate<Collision>() != nullptr)
	ForProtoType(player, opponent3, 20);
	if (opponent4->GetComponentByTemplate<Status>() != nullptr)
	ForProtoType(player, opponent4, 20);
	
	//Should Fixed this
	GetObjectManager()->FindObject("background")->SetScale(GetStateScreenSize());

	rotation_ += 10;
		door->SetRotation(rotation_);

	//if(dot(GetObjectManager()->FindObject("Player")->GetComponentByTemplate<RigidBody>()->GetVelocity(), vector2(0, 1)) > 0)
	//	GetObjectManager()->FindObject("Player")->GetComponentByTemplate<Animation>()->ChangeAnimation("zelda_up");
	//else
	//	GetObjectManager()->FindObject("Player")->GetComponentByTemplate<Animation>()->ChangeAnimation("zelda_down");


	if (Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
	{
		GetSoundMap()->Play("asset/sounds/punch.wav");
	}
	
        if (Input::IsKeyTriggered(GLFW_KEY_O))
		gravity_up *= 1.5;
        if (Input::IsKeyTriggered(GLFW_KEY_P))
		gravity_up /= 1.5;
	if (Input::IsKeyTriggered(GLFW_KEY_0))
		check = !check;
}

void example::ShutDown()
{
	UnLoad();
}

Object* example::BuildAndRegisterStaticObject(std::string object_name, vector2 position, vector2 scale)
{
	GetObjectManager()->AddObject(object_name);
	GetObjectManager()->FindObject(object_name)->SetScale(scale);
	GetObjectManager()->FindObject(object_name)->SetTranslation(position);
	GetObjectManager()->FindObject(object_name)->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	
	//trans form texture, 
	return GetObjectManager()->FindObject(object_name).get();
}
Object* example::BuildAndRegisterDynamicObject(std::string object_name, vector2 position, vector2 scale)
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
void example::SwordPosition(std::string player_str, std::string sword_str)
{
	GetObjectManager()->FindObject(sword_str)->SetTranslation(vector2(
		GetObjectManager()->FindObject(player_str)->GetTransform().GetTranslation().x + 150.f,
		GetObjectManager()->FindObject(player_str)->GetTransform().GetTranslation().y));
}
void example::ForProtoType(Object * object, Object* opponent, float vel_come)
{
	vector2 come = vector2(object->GetTransform().GetTranslation().x - opponent->GetTransform().GetTranslation().x,
		object->GetTransform().GetTranslation().y - opponent->GetTransform().GetTranslation().y);
	vector2 no_come = normalize(come);
	if(magnitude(come) < magnitude(object->GetTransform().GetScale()))
	{
		opponent->GetComponentByTemplate<RigidBody>()->SetVelocity(0);
	}
	else
	opponent->GetComponentByTemplate<RigidBody>()->SetVelocity(vel_come* no_come);
}

void example::snailoption(Object * effect, Object* knife, float angle, float& angle_)
{
	float x_vel, y_vel;
	angle_ += angle;
	//card_velo -= 0.5f;
	if (dt_sum < 2)
		far *= 1.005f;
	else
		far *= 0.995f;
	x_vel = cos(angle_)*(card_velo)+sin(angle_)*(card_velo);
	y_vel = -sin(angle_)*(card_velo) + cos(angle_)*(card_velo);
	effect->GetTransform().SetTranslation(vector2(knife->GetTransform().GetTranslation().x - far * x_vel, knife->GetTransform().GetTranslation().y - far * y_vel));
	if (knife->GetTransform().GetTranslation().y > effect->GetTransform().GetTranslation().y)
	{
		effect->GetTransform().SetDepth(0.95f);
	}
	else
		effect->GetTransform().SetDepth(0.98f);
}
void example::Enchanted(Object * sword, Object* effect,Object * card1, Object * card2, float dt)
{
	float big =0;
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
		 if (dt_sum <2)
			big = 1.01f;
		 else
			big = 0.99f;
	}
	else if(card1->GetMesh().IsVisible() && card2->GetMesh().IsVisible())
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
			sword->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/sword.png");
			sword->GetComponentByTemplate<Sword>()->SetName("sword");
			card_list.clear();
			change_sword = false;
			dt_sum = 0; rota_angle = 0; rota_angle1 = 0; far = 1;
		}
	}
	card1->GetTransform().SetScale(card1->GetTransform().GetScale()* big);
	card2->GetTransform().SetScale(card2->GetTransform().GetScale()* big);
}
void example::thrust(Object * sword, Object* player, float force)
{
    vector2 a = normalize(vector2(sword->GetTransform().GetTranslation().x - player->GetTransform().GetTranslation().x,
        sword->GetTransform().GetTranslation().y - player->GetTransform().GetTranslation().y));
    sword->GetComponentByTemplate<RigidBody>()->SetVelocity(force* a);
}
void example::FollowMe(vector2 mouse, Object * flower)
{
	flower->GetComponentByTemplate<RigidBody>()->SetVelocity(vector2(mouse.x - flower->GetTransform().GetTranslation().x, mouse.y - flower->GetTransform().GetTranslation().y));
}
void example::Flow_leaf(std::vector<Object*> flower)
{
	for (auto i : flower) {
		float pl = rand() % 2;
		if (pl == 1)
			pl = -1;
		else
			pl = 1;
		float p = rand() % 2;
		if (p == 1)
			p = -1;
		else
			p = 1;
		float a = rand() % 100;
		float b = rand() % 100;
		if(i != flower[0])
		i->GetTransform().SetTranslation(vector2(flower[0]->GetTransform().GetTranslation().x + a * p, flower[0]->GetTransform().GetTranslation().y + b * p));
	}
}
void example::Stretch(Object * sword, float bigger)
{
	sword->SetScale(vector2(sword->GetTransform().GetScale().x, sword->GetTransform().GetScale().y +bigger));
}
void example::Power_shot()
{
	if (isshot != true)
	{
		isshot = true;
		std::string power = "power";
		GetObjectManager()->AddObject(power);
		vector2 a = normalize(vector2(sword->GetTransform().GetTranslation().x - player->GetTransform().GetTranslation().x,
			sword->GetTransform().GetTranslation().y - player->GetTransform().GetTranslation().y));
		GetObjectManager()->FindObject(power)->SetMesh(mesh::CreateBox());
		GetObjectManager()->FindObject(power).get()->SetRotation(*sword->GetTransform().GetRotation() + 90);
		GetObjectManager()->FindObject(power).get()->SetScale({ sword->GetTransform().GetScale().x,sword->GetTransform().GetScale().y });
		GetObjectManager()->FindObject(power).get()->SetTranslation({ sword->GetTransform().GetTranslation().x, sword->GetTransform().GetTranslation().y });
		GetObjectManager()->FindObject(power).get()->AddComponent(new Collision(box_, vector2(sword->GetTransform().GetTranslation().x, sword->GetTransform().GetTranslation().y), { sword->GetTransform().GetScale().x, sword->GetTransform().GetScale().y }));
		GetObjectManager()->FindObject(power).get()->AddComponent(new RigidBody());
		GetObjectManager()->FindObject(power).get()->GetComponentByTemplate<RigidBody>()->SetVelocity(200 * a);
		GetObjectManager()->FindObject(power).get()->AddComponent(new Animation("asset/images/shot.png", "power", 4, 0.25));
		GetObjectManager()->FindObject(power).get()->AddComponent(new Character(ObjectType::shot));
		GetObjectManager()->FindObject(power).get()->AddComponent(new Status(1, 1, 1.f));
	}
}
void example::find(std::string card_)
{
	card_list.push_back(GetObjectManager()->FindObject(card_).get());
}

Object* example::AwesomeEfftect(std::string stuff, vector2 position)
{
	a_stuff += 1;
	GetObjectManager()->AddObject(a_stuff);
	GetObjectManager()->FindObject(a_stuff)->SetMesh(mesh::CreateBox());
	GetObjectManager()->FindObject(a_stuff).get()->SetScale({ 50.f,50.f }

	);
	GetObjectManager()->FindObject(a_stuff).get()->SetTranslation({ position});
	GetObjectManager()->FindObject(a_stuff).get()->AddComponent(new Collision(box_, {}, { 50.0f, 50.0f }));
	GetObjectManager()->FindObject(a_stuff).get()->AddComponent(new RigidBody());
	GetObjectManager()->FindObject(a_stuff).get()->AddComponent(new Sprite());
	GetObjectManager()->FindObject(a_stuff).get()->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/"+stuff + ".png");
	GetObjectManager()->FindObject(a_stuff).get()->AddComponent(new Character(ObjectType::card));

	return GetObjectManager()->FindObject(a_stuff).get();
}
void example::ComePlayer(Object * object, Object * opponent, float vel_come)
{
	vector2 come = vector2(object->GetTransform().GetTranslation().x - opponent->GetTransform().GetTranslation().x,
		object->GetTransform().GetTranslation().y - opponent->GetTransform().GetTranslation().y);
	vector2 no_come = normalize(come);
		opponent->GetComponentByTemplate<RigidBody>()->SetVelocity(vel_come* no_come);
}

void example::MakeManyEffect(std::string card)
{
	dump.push_back(AwesomeEfftect(card, { 300.f,0.f }));
	dump.push_back(AwesomeEfftect(card, { 0.f,300.f }));
	dump.push_back(AwesomeEfftect(card, { -300.f,0.f }));
	dump.push_back(AwesomeEfftect(card, { 0.f,-300.f }));
	dump.push_back(AwesomeEfftect(card, { 300.f,300.f }));
	dump.push_back(AwesomeEfftect(card, { -300.f,300.f }));
	dump.push_back(AwesomeEfftect(card, { 300.f,-300.f }));
	dump.push_back(AwesomeEfftect(card, { -300.f,-300.f }));
}

void example::Shot(std::string name)
{
	GetObjectManager()->AddObject(name);
	GetObjectManager()->FindObject(name)->SetMesh(mesh::CreateBox());
	vector2 a = normalize(vector2(Input::GetMousePos(Graphics::checking_zoom).x - player->GetTransform().GetTranslation().x,
		Input::GetMousePos(Graphics::checking_zoom).y - player->GetTransform().GetTranslation().y));

	std::cout << a.x << ", " << a.y <<std::endl;

	GetObjectManager()->FindObject(name).get()->SetRotation(*sword->GetTransform().GetRotation() + 90);
	GetObjectManager()->FindObject(name).get()->SetScale({ sword->GetTransform().GetScale().x,sword->GetTransform().GetScale().y });
	GetObjectManager()->FindObject(name).get()->SetTranslation({ sword->GetTransform().GetTranslation().x, sword->GetTransform().GetTranslation().y });
	GetObjectManager()->FindObject(name).get()->AddComponent(new Collision(box_, vector2(sword->GetTransform().GetTranslation().x, sword->GetTransform().GetTranslation().y), { sword->GetTransform().GetScale().x, sword->GetTransform().GetScale().y }));
	GetObjectManager()->FindObject(name).get()->AddComponent(new RigidBody());
	GetObjectManager()->FindObject(name).get()->GetComponentByTemplate<RigidBody>()->SetVelocity(200 * a);
	GetObjectManager()->FindObject(name).get()->AddComponent(new Animation("asset/images/shot.png", "power", 4, 0.25));
	GetObjectManager()->FindObject(name).get()->AddComponent(new Character(ObjectType::shot));
	GetObjectManager()->FindObject(name).get()->AddComponent(new Status(1, 1, 1.f));
}
