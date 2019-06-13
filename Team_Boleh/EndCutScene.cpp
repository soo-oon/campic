#include "EndCutScene.hpp"

void EndCutScene::Initialize()
{
	start = new Object();
	start->SetTranslation({ 0, 0 });
	start->SetScale({ static_cast<float>(Application_.GetGLFWvidmode()->width), static_cast<float>(Application_.GetGLFWvidmode()->height) });
	start->SetDepth(-0.7f);
	start->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	start->SetObjectType(ObjectType::Background);
	start->AddComponent(new Sprite("asset/images/Page/WinPage.png"));

	end = new Object();
	end->SetTranslation({ 0, 0 });
	end->SetScale({ static_cast<float>(Application_.GetGLFWvidmode()->width), static_cast<float>(Application_.GetGLFWvidmode()->height) });
	end->SetDepth(-0.6f);
	end->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	end->SetObjectType(ObjectType::Background);
	end->AddInitComponent(new Animation("asset/images/Page/EndCutScene.png", "end",15, 0.5f, false));
	end->GetComponentByTemplate<Animation>()->SetIsActive(false);

	Objectmanager_.AddObject(end);
	Objectmanager_.AddObject(start);
}

void EndCutScene::Update(float dt)
{
	timer += dt;

	if (!is_end_start_sprite)
	{
		if (timer >= 3.0f)
		{
			is_end_start_sprite = true;
		}
	}
	else
	{
		if (!is_start_animation)
		{
			if (timer >= 6.0f)
			{
				start->SetInvisible();
				end->GetComponentByTemplate<Animation>()->SetIsActive(true);
				is_start_animation = true;
			}
		}
	}

	if (is_start_animation)
	{
		if (end->GetComponentByTemplate<Animation>()->IsDone())
		{
			SetLevelIndicator("Credit");
			StateManager_.ToCredit();
		}
	}
}

void EndCutScene::ShutDown()
{
	UnLoad();
}
