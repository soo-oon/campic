#include "example_level.hpp"
#include <iostream>
#include "Sprite.hpp"
#include "RigidBody.hpp"
#include "Input.hpp"
#include "WorldPhysics.h"
#include "Animation.hpp"
#include "Collision.hpp"
#include "vector2.hpp"
#include "Character.hpp"
#include <limits.h>

void example::blackhole(Object* Ob, Object* Ob1)
{
	for (auto it = GetObjectManager()->GetObjectMap().begin();
		it != GetObjectManager()->GetObjectMap().end(); ++it)
	{
		vector2 black = 0;
		float* rotation = it->second.get()->GetTransform().GetRotation();
		if (it->second.get() != Ob && it->second.get() != Ob1)
		{
			black = vector2(it->second.get()->GetTransform().GetTranslation().x - Ob->GetTransform().GetTranslation().x, it->second.get()->GetTransform().GetTranslation().y - Ob->GetTransform().GetTranslation().y);
			black /= 4000;
			for (int i = 0; i < 10; i++)
			{
				it->second.get()->GetTransform().SetTranslation(it->second.get()->GetTransform().GetTranslation() - black );
			}
			*rotation += 10;
			it->second.get()->SetRotation(*rotation);
		}
	}
}

void example::move_convex_object(float dt, Object* Ob)
{
	float velo = 100;
	limit_time += dt;
	if(limit_time > 1.0f)
	{
		pm *= -1;
		velo *= pm;
		Ob->GetComponentByTemplate<RigidBody>()->SetVelocity(vector2(velo, 0));
		limit_time = 0;
		//std::cout << GetObjectManager()->FindObject("convex_object")->GetComponentByTemplate<Physics>()->GetVelocity().x << std::endl;
	}
}

void example::Initialize()
{
	Load();
	player = BuildAndRegisterDynamicObject("player", vector2(0, 0), vector2(100.f, 100.f));
	player->AddComponent(new Animation("asset/images/action.png", "zelda_down", 10, 0.1f));
	player->GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/attack.png", "attack", 3, 0.25f, false);
	player->GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/action_c.png", "zelda_up", 10, 0.1f);
	player->AddComponent(new Collision(box_, {}, {100.0f, 100.0f}));
	player->AddComponent(new Character(ObjectType::player));

        // TODO
        health_bar = BuildAndRegisterDynamicObject("health", vector2(0.0f, 0.5f), vector2(150.f/ player->GetTransform().GetScale().x, 
			10.f/ player->GetTransform().GetScale().y));
        health_bar->GetTransform().SetParent(&player->GetTransform());
        health_bar->AddComponent(new Sprite);
        health_bar->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/health.png");

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

        shot = BuildAndRegisterDynamicObject("shot", vector2(-350, -350), vector2(75.f, 75.f));
        shot->AddComponent(new Animation("asset/images/shot.png", "shot", 4, 0.25));
        shot->AddComponent(new RigidBody());
        shot->GetMesh().Invisible();

	scol = BuildAndRegisterDynamicObject("scol", vector2(-300, 300), vector2(75.f, 75.f));
	scol->AddComponent(new Animation("asset/images/scol.png", "scol", 6, 0.25));
	scol->AddComponent(new RigidBody());
	scol->AddComponent(new Collision(box_, {}, { 75.0f, 75.0f }));
	scol->GetComponentByTemplate<Collision>()->SetRestitutionType(RestitutionType::stop);
	scol->AddComponent(new Character(ObjectType::opponent));
	
        dia = BuildAndRegisterDynamicObject("dia", vector2(350, -100), vector2(25.f, 25.f));
        dia->AddComponent(new Sprite());
        dia->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/dia.png");
        dia->AddComponent(new Character(ObjectType::none));
	dia->AddComponent(new RigidBody());
	dia->GetMesh().Invisible();

	dia1 = BuildAndRegisterDynamicObject("dia1", vector2(420, -100), vector2(50.f, 50.f));
	dia1->AddComponent(new Sprite());
	dia1->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/dia.png");
	dia1->AddComponent(new Collision(box_, {}, {50.0f, 50.0f}));
	dia1->GetComponentByTemplate<Collision>()->SetRestitutionType(RestitutionType::stop);
    dia1->AddComponent(new Character(ObjectType::card));


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
	heart1 = BuildAndRegisterDynamicObject("heart1", vector2(420, 100), vector2(50.f, 50.f));
	heart1->AddComponent(new Sprite());
	heart1->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/heart.png");
	heart1->AddComponent(new Collision(box_, {}, {50.0f, 50.0f}));
	heart1->GetComponentByTemplate<Collision>()->SetRestitutionType(RestitutionType::stop);
	heart1->AddComponent(new Character(ObjectType::card));

	sword = BuildAndRegisterStaticObject("sword", vector2(0, 0), vector2(75, 75));
	sword->AddComponent(new Sprite());
	sword->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/trash.png");
	sword->AddComponent(new Collision(box_, {}, { 40.0f, 80.0f }));
        sword->AddComponent(new RigidBody());
	sword->GetComponentByTemplate<Collision>()->SetRestitutionType(RestitutionType::none);
	sword->AddComponent(new Character(ObjectType::sword));
	sword->SetDepth(0.978f);


	spark = BuildAndRegisterDynamicObject("spark", vector2(200, 0), vector2(100.f, 100.f));
	spark->AddComponent(new Animation("asset/images/sprite.png", "spark", 7, 0.08f));
	spark->GetMesh().Invisible();

	sonic = BuildAndRegisterDynamicObject("sonic", vector2(0, -200), vector2(150.f, 150.f));
	sonic->AddComponent(new Animation("asset/images/example2.png", "sonic", 10, 0.1f));
	sonic->AddComponent(new RigidBody());
	sonic->AddComponent(new Collision(box_, {},{150.0f, 150.0f} ));
	sonic->GetComponentByTemplate<Collision>()->SetRestitutionType(RestitutionType::stop);
	sonic->AddComponent(new Character(ObjectType::opponent));
	
	background = BuildAndRegisterDynamicObject("background", vector2(0,0), vector2(150.f, 150.f));
	background->SetDepth(0.99f);
	background->AddComponent(new Sprite());
	background->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/background.png");
	
	GetWorldPhyics()->Gravity_on(GetObjectManager());
}

void example::Update(float dt)
{
    Camera* temp_camera = GetObjectManager()->FindObject("camera")->GetComponentByTemplate<Camera>();
        if (Input::IsKeyTriggered(GLFW_KEY_T))
        {
            if (!change_sword)
                change_sword = true;
            else
                change_sword = false;
        }
	if (Input::IsKeyTriggered(GLFW_KEY_2))
		ChangeLevel("test");
	if (Input::IsKeyTriggered(GLFW_KEY_3))
		ChangeLevel("MapEditorTest");
        if (sword->GetComponentByTemplate<RigidBody>()->GetVelocity() != vector2(0, 0))
            sword->GetComponentByTemplate<RigidBody>()->SetVelocity(vector2(0, 0));

    if(Input::IsKeyPressed(GLFW_KEY_X))
    {
	    if (!isshot)
		    isshot = true;
	    else
		    isshot = false;
    }

    if (isshot)
    {
	    shot->GetMesh().Visible();
	    thrust(shot, player, 100);
    }
    else
    {
	    shot->GetTransform().SetTranslation(vector2(sword->GetTransform().GetTranslation().x, sword->GetTransform().GetTranslation().y));
	    shot->GetTransform().SetRotation(*sword->GetTransform().GetRotation()+90);
    }
        SwordSwing(Input::GetMousePos(temp_camera->GetZoomValue()), player, sword);

	if (Input::IsKeyTriggered(GLFW_KEY_Q) && player->GetComponentByTemplate<Collision>()->GetRestitutionType() == RestitutionType::exit)
		ChangeLevel("test");

	ForProtoType(player, scol, 20);
	ForProtoType(player, slime, 20);

	Attact(sword);
	spark->GetTransform().SetTranslation(vector2(sword->GetTransform().GetTranslation().x, sword->GetTransform().GetTranslation().y));
	if(change_sword)
	{
		Enchanted(sword, spark, dia, heart, dt);

	}
	
	//Should Fixed this
	GetObjectManager()->FindObject("background")->SetScale(GetStateScreenSize());

	rotation_ += 10;
		door->SetRotation(rotation_);

	if(dot(GetObjectManager()->FindObject("player")->GetComponentByTemplate<RigidBody>()->GetVelocity(), vector2(0, 1)) > 0)
		GetObjectManager()->FindObject("player")->GetComponentByTemplate<Animation>()->ChangeAnimation("zelda_up");
	else
		GetObjectManager()->FindObject("player")->GetComponentByTemplate<Animation>()->ChangeAnimation("zelda_down");

        if(Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
        {
            player->GetComponentByTemplate<Animation>()->ChangeAnimation("attack");
        }

        if (dot(normalize(GetObjectManager()->FindObject("player")->GetComponentByTemplate<RigidBody>()->GetVelocity()), vector2(0, 1)) > 0)
        {
            player->GetComponentByTemplate<Animation>()->ChangeAnimation("zelda_up");
        }
        else
        {
            player->GetComponentByTemplate<Animation>()->ChangeAnimation("zelda_down");
        }
   
	GetWorldPhyics()->Movement_Velocity(*GetObjectManager()->FindObject("player"));
	
        if (Input::IsKeyTriggered(GLFW_KEY_O))
            gravity_up *= 1.5;
        if (Input::IsKeyTriggered(GLFW_KEY_P))
            gravity_up /= 1.5;

            GetWorldPhyics()->Gravity_on(GetObjectManager(), gravity_up);
	if (Input::IsKeyTriggered(GLFW_KEY_0))
		check = !check;

	if(check)
		GetWorldPhyics()->Movement_Velocity(*GetObjectManager()->FindObject("player").get());
	else
		GetWorldPhyics()->Movement_by_key(*GetObjectManager()->FindObject("player").get());

	if(Input::IsKeyPressed(GLFW_KEY_SPACE))
	{
		blackhole(GetObjectManager()->FindObject("player").get(),GetObjectManager()->FindObject("background").get());
	}
	//GetObjectManager()->FindObject("player")->GetComponentByTemplate<Animation>()->Update(dt);

	//GetObjectManager()->FindObject("sonic")->GetComponentByTemplate<Animation>()->Update(dt);
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
	x_vel = cos(angle_)*(card_velo)+sin(angle_)*(card_velo);
	y_vel = -sin(angle_)*(card_velo) + cos(angle_)*(card_velo);
	effect->GetTransform().SetTranslation(vector2(knife->GetTransform().GetTranslation().x - x_vel, knife->GetTransform().GetTranslation().y - y_vel));
	if (knife->GetTransform().GetTranslation().y > effect->GetTransform().GetTranslation().y)
	{
		effect->GetTransform().SetDepth(0.95f);
	}
	else
		effect->GetTransform().SetDepth(0.98f);
}
void example::Enchanted(Object * sword, Object* effect,Object * card1, Object * card2, float dt)
{
	snailoption(card1, sword, -0.02f, rota_angle);
	snailoption(card2, sword, 0.02f, rota_angle1);

	if (dt_sum < 10)
	{
		dt_sum += dt;
		if (!card1->GetMesh().IsVisible() && !card2->GetMesh().IsVisible())
		{
			card1->GetMesh().Visible();
			card2->GetMesh().Visible();
		}
	}
	else if(card1->GetMesh().IsVisible() && card2->GetMesh().IsVisible())
	{
		card1->GetMesh().Invisible();
		card2->GetMesh().Invisible();
	}
	else
	{
		if (dt_sum < 15)
		{
			dt_sum += dt;
			if (!effect->GetMesh().IsVisible())
				effect->GetMesh().Visible();
		}
		else if (effect->GetMesh().IsVisible())
		{
			effect->GetMesh().Invisible();
			sword->GetTransform().SetScale(vector2(200.f, 150.f));
			sword->GetComponentByTemplate<Collision>()->ChangeCollisionBoxScale(vector2(40.0f, 150.0f));
			sword->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/sword.png");
		}
	}

}
void example::thrust(Object * sword, Object* player, float force)
{
    vector2 a = normalize(vector2(sword->GetTransform().GetTranslation().x - player->GetTransform().GetTranslation().x,
        sword->GetTransform().GetTranslation().y - player->GetTransform().GetTranslation().y));
    sword->GetComponentByTemplate<RigidBody>()->SetVelocity(force* a);
}
void example::SwordSwing(vector2 mouse_position, Object* player, Object* sword)
{
	vector2 swing_direction = normalize(vector2(mouse_position.x - player->GetTransform().GetTranslation().x,
		mouse_position.y - player->GetTransform().GetTranslation().y));
	sword->SetTranslation(vector2(
		player->GetTransform().GetTranslation().x + swing_direction.x *player->GetTransform().GetScale().x,
		player->GetTransform().GetTranslation().y + swing_direction.y *player->GetTransform().GetScale().y));
        float anglerad = atan2(mouse_position.y - player->GetTransform().GetTranslation().y, mouse_position.x - player->GetTransform().GetTranslation().x);
        float angledeg = (180 / 3.14f )* anglerad;
        sword->SetRotation(angledeg - 90);
		sword->GetComponentByTemplate<Collision>()->GetCollisionTransform().SetRotation(angledeg - 90);
        //float a = dot(sword->GetTransform().GetTranslation(), vector2(0, 1))/ magnitude(sword->GetTransform().GetTranslation());
        //if(mouse_position.x > player->GetTransform().GetTranslation().x)
        //{
        //    std::cout <<"mouse : "<< mouse_position.x <<"player : " << player->GetTransform().GetTranslation().x << std::endl;
        //    a = 360 - acos(a)*(180 / 3.14);
        //}
        //else
        //a = acos(a)*(180/3.14);
        //std::cout << a << std::endl;
        //sword->SetRotation(a);
}

void example::Attact(Object * object)
{
	if (Input::IsMousePressed(GLFW_MOUSE_BUTTON_LEFT))
		object->GetComponentByTemplate<Collision>()->ToggleIsDamaged();
}