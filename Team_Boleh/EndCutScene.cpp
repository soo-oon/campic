#include "EndCutScene.hpp"

void EndCutScene::Initialize()
{

     timer = 0.f;
     is_end_start_sprite = false;
     is_start_animation = false;

	AudioManager_.LoadSong("asset/sounds/EndCutScene.mp3");
	AudioManager_.PlaySong("asset/sounds/EndCutScene.mp3");
	start = new Object();
	start->SetTranslation({ 0, 0 });
	start->SetScale({ static_cast<float>(Application_.GetGLFWvidmode()->width), static_cast<float>(Application_.GetGLFWvidmode()->height) });
	start->SetDepth(-0.7f);
	start->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	start->SetObjectType(ObjectType::Background);
	start->AddComponent(new Sprite("asset/images/Page/WinPage.png"));
	start->GetMesh().Invisible();

	end = new Object();
	end->SetTranslation({ 0, 0 });
	end->SetScale({ static_cast<float>(Application_.GetGLFWvidmode()->width), static_cast<float>(Application_.GetGLFWvidmode()->height) });
	end->SetDepth(-0.6f);
	end->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	end->SetObjectType(ObjectType::Background);
	end->AddInitComponent(new Animation("asset/images/Page/EndCutScene1.png", "end1",11, 0.3f, false));
	
	//end->GetComponentByTemplate<Animation>()->SetIsActive(false);

	end2 = new Object();
	end2->SetTranslation({ 0, 0 });
	end2->SetScale({ static_cast<float>(Application_.GetGLFWvidmode()->width), static_cast<float>(Application_.GetGLFWvidmode()->height) });
	end2->SetDepth(-0.6f);
	end2->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	end2->SetObjectType(ObjectType::Background);
	end2->AddInitComponent(new Animation("asset/images/Page/EndCutScene2.png", "end2", 15, 0.5f, false));
	end2->GetComponentByTemplate<Animation>()->SetIsActive(false);

	Objectmanager_.AddObject(end);
	Objectmanager_.AddObject(end2);
	Objectmanager_.AddObject(start);
}

void EndCutScene::Update(float dt)
{
	timer += dt;

	if (!is_end_start_sprite)
	{
		if (timer >= 5.0f)
		{
			end->GetComponentByTemplate<Animation>()->SetIsActive(false);
			start->GetMesh().Visible();
			is_end_start_sprite = true;
		}
	}
	else
	{
		if (!is_start_animation)
		{
			if (timer >= 10.0f)
			{
				start->SetInvisible();
				end->GetMesh().Invisible();
				end2->GetComponentByTemplate<Animation>()->SetIsActive(true);
				is_start_animation = true;
			}
		}
	}

	if (is_start_animation)
	{
		if (timer >= 19.f)
		{
			SetLevelIndicator("Credit");
			StateManager_.ToCredit();
		}
	}

    if(Input::IsKeyAnyTriggered())
    {
        SetLevelIndicator("Credit");
        StateManager_.ToCredit();
    }
}

void EndCutScene::ShutDown()
{
	UnLoad();
}
