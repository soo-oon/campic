#include "StartCutScene.hpp"

void StartCutScene::Initialize()
{
	AudioManager_.LoadSong("asset/sounds/StartCutScene.mp3");
	AudioManager_.PlaySong("asset/sounds/StartCutScene.mp3");
	start = new Object();
	start->SetTranslation({ 0, 0 });
	start->SetScale({ static_cast<float>(Application_.GetGLFWvidmode()->width), static_cast<float>(Application_.GetGLFWvidmode()->height) });
	start->SetDepth(-0.6f);
	start->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	start->SetObjectType(ObjectType::Background);
	start->AddComponent(new Sprite("asset/images/Page/Start1.png"));

	start1 = new Object();
	start1->SetTranslation({ 0, 0 });
	start1->SetScale({ static_cast<float>(Application_.GetGLFWvidmode()->width), static_cast<float>(Application_.GetGLFWvidmode()->height) });
	start1->SetDepth(-0.6f);
	start1->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	start1->SetObjectType(ObjectType::Background);
	start1->AddInitComponent(new Animation("asset/images/Page/StartCutScene.png", "cut", 20, 0.1f, false));
	start1->GetComponentByTemplate<Animation>()->SetIsActive(false);

	Objectmanager_.AddObject(start);
	Objectmanager_.AddObject(start1);
}

void StartCutScene::Update(float dt)
{
	timer += dt;

	if (!is_end_start_sprite)
	{
		if (timer >= 3.0f)
		{
			start->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/Page/Start2.png");
			is_end_start_sprite = true;
		}
	}
	else
	{
		if(!is_start_animation)
		{
			if (timer >= 6.0f)
			{
				start->SetInvisible();
				start1->GetComponentByTemplate<Animation>()->SetIsActive(true);
				is_start_animation = true;
			}
		}
	}

	if(is_start_animation)
	{
		if(start1->GetComponentByTemplate<Animation>()->IsDone())
		{
			SetLevelIndicator("Level1");
			ChangeLevel("Level1");
		}
	}
}

void StartCutScene::ShutDown()
{
	UnLoad();
}
