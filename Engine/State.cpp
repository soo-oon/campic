#include "State.hpp"
#include "JSON.hpp"
#include "status.hpp"
#include "Character.hpp"
#include "Player.hpp"

void State::UpdateObjManager(float dt)
{
	objectmanager->Update(dt);
}

void State::Load()
{
	change_level.clear();
	level_change = false;
	objectmanager = std::make_unique<Objectmanager>();
	json = new JSON();
	sound = new Sound();
	sound->Initialize();
}

void State::UnLoad()
{
	objectmanager.release();
	objectmanager = nullptr;
	delete json;
	delete sound;
}

void State::AddPlayer()
{
	objectmanager->AddObject("Player");
	objectmanager->FindObject("Player")->AddComponent(new Player());

	objectmanager->AddObject("Sword");
	objectmanager->FindObject("Sword")->SetScale({75.0f, 75.0f});
	auto temp_translation = objectmanager->FindObject("Player")->GetTransform().GetTranslation();
	objectmanager->FindObject("Sword")->SetTranslation(temp_translation);
	objectmanager->FindObject("Sword")->SetMesh(mesh::CreateBox());
	objectmanager->FindObject("Sword")->AddComponent(new Sprite());
	objectmanager->FindObject("Sword")->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/trash.png");
	objectmanager->FindObject("Sword")->AddComponent(new Collision(box_, {}, { 40.0f, 40.0f }));
	objectmanager->FindObject("Sword")->AddComponent(new RigidBody());
	objectmanager->FindObject("Sword")->GetComponentByTemplate<Collision>()->SetRestitutionType(RestitutionType::none);
	objectmanager->FindObject("Sword")->AddComponent(new Character(ObjectType::sword));
	objectmanager->FindObject("Sword")->AddComponent(new Status(5, 1, 1.f));
	objectmanager->FindObject("Sword")->SetDepth(0.978f);
}

void State::ChangeLevel(std::string ID)
{
	level_change = true;
	change_level = ID;
}
