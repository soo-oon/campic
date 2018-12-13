#include "StartMenu.hpp"
#include "Input.hpp"

#define StartButton			"asset/images/UI/StartButton.png"
#define StartButtonSelect	"asset/images/UI/StartButtonSelect.png"
#define OptionButton		"asset/images/UI/OptionButton.png"
#define OptionButtonSelect	"asset/images/UI/OptionButtonSelect.png"
#define QuitButton			"asset/images/UI/QuitButton.png"
#define QuitButtonSelect	"asset/images/UI/QuitButtonSelect.png"

enum class button : int
{
	Start,
	Option,
	Quit
};

void StartMenu::Initialize()
{
	//Load();
	//start - stages
	//option - something.... map editor
	//quit
	SetUpButtons("MenuBackground", vector2(1280.f, 1000.f), vector2(0.f, 0.f), "asset/images/UI/Menu_background.png");
	SetUpButtons("StartButton", vector2(348.f, 86.f), vector2(0.f, 00.f), StartButtonSelect);
	SetUpButtons("OptionButton", vector2(348.f, 86.f), vector2(0.f, -150.f), OptionButton);
	SetUpButtons("QuitButton", vector2(348.f, 86.f), vector2(0.f, -300.f), QuitButton);

	Start = GetObjectManager()->FindObject("StartButton").get();
	Option = GetObjectManager()->FindObject("OptionButton").get();
	Quit = GetObjectManager()->FindObject("QuitButton").get();
}

void StartMenu::Update(float dt)
{
	if (Input::IsKeyTriggered(GLFW_KEY_ENTER))
	{
		if (StartOn)
			ChangeLevel("example");
		else if (OptionOn)
			ChangeLevel("MapEditorTest");
		else if (QuitOn)
			Input::SetKeyPressed(GLFW_KEY_ESCAPE, GLFW_PRESS);
	}

	ChangeSelectedMenu();
}

void StartMenu::ShutDown()
{
	//UnLoad();
}

void StartMenu::SetUpButtons(std::string obj_name, vector2 size, 
							vector2 position, std::string texture_path)
{
	GetObjectManager()->AddObject(obj_name);
	GetObjectManager()->FindObject(obj_name)->SetScale(size);
	GetObjectManager()->FindObject(obj_name)->SetTranslation(position);
	GetObjectManager()->FindObject(obj_name)->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	if(obj_name == "MenuBackground")
		GetObjectManager()->FindObject(obj_name)->SetDepth(0.0f);
	else
		GetObjectManager()->FindObject(obj_name)->SetDepth(-1.0f);
	GetObjectManager()->FindObject(obj_name)->AddComponent(new Sprite());
	GetObjectManager()->FindObject(obj_name)->GetComponentByTemplate<Sprite>()->Texture_Load(texture_path);
	GetObjectManager()->FindObject(obj_name)->texture_path = texture_path;
}

void StartMenu::ChangeSelectedMenu()
{

	if (Input::IsKeyTriggered(GLFW_KEY_DOWN))
		select_button_id++;
	if (Input::IsKeyTriggered(GLFW_KEY_UP))
		select_button_id--;

	if (select_button_id < 0)
		select_button_id = (int)(button::Quit);
	else if (select_button_id > (int)(button::Quit))
		select_button_id = (int)(button::Start);

	if (Input::IsKeyTriggered(GLFW_KEY_DOWN) || Input::IsKeyTriggered(GLFW_KEY_UP))
		ChangeTexture(select_button_id);
}

void StartMenu::ChangeTexture(int type)
{
	switch (type)
	{
	case (int)button::Start:
		if (StartOn)
			Start->GetComponentByTemplate<Sprite>()->Texture_Load(StartButton);
			else
			Start->GetComponentByTemplate<Sprite>()->Texture_Load(StartButtonSelect);
		StartOn = true;
		OptionOn = false;
		QuitOn = false;
		Option->GetComponentByTemplate<Sprite>()->Texture_Load(OptionButton);
		Quit->GetComponentByTemplate<Sprite>()->Texture_Load(QuitButton);
		break;
	case (int)button::Option:
		if (OptionOn)
			Option->GetComponentByTemplate<Sprite>()->Texture_Load(OptionButton);
			else
			Option->GetComponentByTemplate<Sprite>()->Texture_Load(OptionButtonSelect);
		StartOn = false;
		OptionOn = true;
		QuitOn = false;
		Start->GetComponentByTemplate<Sprite>()->Texture_Load(StartButton);
		Quit->GetComponentByTemplate<Sprite>()->Texture_Load(QuitButton);
		break;
	case (int)button::Quit:
		if (QuitOn)
			Quit->GetComponentByTemplate<Sprite>()->Texture_Load(QuitButton);
		else
			Quit->GetComponentByTemplate<Sprite>()->Texture_Load(QuitButtonSelect);
		StartOn = false;
		OptionOn = false;
		QuitOn = true;
		Start->GetComponentByTemplate<Sprite>()->Texture_Load(StartButton);
		Option->GetComponentByTemplate<Sprite>()->Texture_Load(OptionButton);
		break;
	}
}

