#include "LoseScene.hpp"

void LoseScene::Initialize()
{
	background = new Object();
	background->SetTranslation(vector2(0,0));
	background->SetScale({ static_cast<float>(Application_.GetGLFWvidmode()->width + 100), static_cast<float>(Application_.GetGLFWvidmode()->height + 100) });
	background->SetDepth(0.99f);
	background->SetObjectType(ObjectType::None);
	background->SetMesh(mesh::CreateBox());
	background->AddComponent(new Animation("asset/images/Page/BackgroundDay.png", "day", 16, 0.15f, true));
	background->GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/Page/BackgroundAfernoon.png", "sunset", 16, 0.15f, true);
	background->GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/Page/BackgroundNight.png", "night", 16, 0.15f, true);

    m_game_over = new Object();
    m_game_over->SetTranslation({ 0,0 });
    m_game_over->SetScale({1080,720});
    m_game_over->SetDepth(0.9f);
    m_game_over->SetObjectType(ObjectType::None);
    m_game_over->SetMesh(mesh::CreateBox());
    m_game_over->AddComponent(new Sprite("asset/images/Page/GameOver.png"));

    m_restart= new Object();
    m_restart->SetTranslation({ -150, -450 });
    m_restart->SetScale({ 200,96 });
    m_restart->SetDepth(HUD_BUTTON);
    m_restart->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
    m_restart->SetObjectType(ObjectType::Button);
    m_restart->AddInitComponent(new Sprite("asset/images/UI/Restart.png"));

    m_menu = new Object();
    m_menu->SetTranslation({ 150, -450 });
    m_menu->SetScale({ 182,96 });
    m_menu->SetDepth(HUD_BUTTON);
    m_menu->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
    m_menu->SetObjectType(ObjectType::Button);
    m_menu->AddInitComponent(new Sprite("asset/images/UI/Back.png"));

    mouse_icon = new Object();
    mouse_icon->SetTranslation({ 0,0 });
    mouse_icon->SetScale({ 50,50 });
    mouse_icon->SetDepth(-0.9f);
    mouse_icon->SetObjectType(ObjectType::None);
    mouse_icon->SetMesh(mesh::CreateBox());
    mouse_icon->AddComponent(new Sprite("asset/images/UI/MouseCursor.png"));

    TakePrevLevel();

    Objectmanager_.AddObject(m_game_over);
    Objectmanager_.AddObject(mouse_icon);
	Objectmanager_.AddObject(background);
    button_.AddObject(m_menu);
    button_.AddObject(m_restart);

	change = true;
}

void LoseScene::Update(float dt)
{
    mouse_icon->SetTranslation(Input::GetMousePos());

	if (change)
	{
		switch (StateManager_.GetChapter())
		{
		case 1:
		{
			background->GetComponentByTemplate<Animation>()->ChangeAnimation("day");
			change = false;
			break;
		}
		case 2:
		{
			background->GetComponentByTemplate<Animation>()->ChangeAnimation("sunset");
			change = false;
			break;
		}
		case 3:
		{
			background->GetComponentByTemplate<Animation>()->ChangeAnimation("night");
			change = false;
			break;
		}

		default:
			break;
		}
	}

    if (button_.IntersectionCheck(Input::GetMousePos()))
    {
        button_.GetSelect().first->GetMesh().ChangeColor({ 255,255,0 });
        if (Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
        {
            if (button_.GetSelect().first == m_restart)
            {
                    AudioManager_.PlaySFX("asset/sounds/Button.wav", 0.1f);
                    SetLevelIndicator(m_this_level);
                    ChangeLevel(m_this_level);
                    button_.RemoveContainer();
            }
            else if(button_.GetSelect().first == m_menu)
            {
                AudioManager_.PlaySFX("asset/sounds/Button.wav", 0.1f);
                button_.RemoveContainer();
                StateManager_.BackToMainMenu();
            }
        }
    }
    else
    {
        for (auto&i : button_.GetContainer())
        {
            i.get()->GetMesh().ChangeColor({ 255, 255, 255 });
        }
    }

}

void LoseScene::ShutDown()
{
    UnLoad();
}

void LoseScene::TakePrevLevel()
{
    m_this_level = StateManager_.GetPrevLevel();
}
