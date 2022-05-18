#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Intro.h"
#include "LevelManagement.h"
#include "Ease.h"


#include "Defs.h"
#include "Log.h"

Intro::Intro(bool isActive) : Module(isActive)
{
	name.Create("intro");
	toSave = false;
	saveConfigs = false;
}

// Destructor
Intro::~Intro()
{}

// Called before render is available
bool Intro::Awake()
{
	LOG("Loading Intro Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Intro::Start()
{

	intro = app->audio->LoadFx("Assets/audio/fx/intro.wav");
	app->audio->PlayFx(intro);
	waitTime = 200;
	img = app->tex->Load("Assets/Sprites/UI/screen_logo.jpg");
	rect = { 0, 0, 1280, 720 };
	logoXpos = - 100;
	return true;
}

// Called each loop iteration
bool Intro::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Intro::Update(float dt)
{
	
	if (counter < easingTime)
	{

		auto easingFunction = getEasingFunction(EaseOutBounce);
		double progress = easingFunction(UpdateProgress(counter, 0, 100, 0, 1));
		logoXpos =(int) UpdateProgress(progress, 0, 1, -100, 0);
		counter++;
	}

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		waitTime = 0;
	}
	else
	{
		waitTime -= 1;
	}

	if (waitTime < 0)
		app->levelManagement->LoadScene(GameScene::START);
	
	return true;
}

// Called each loop iteration
bool Intro::PostUpdate()
{

	app->render->DrawTexture(img, logoXpos, 0, &rect, 0, 0, 0, 0, 0.5f);

	return true;
}

// Called before quitting
bool Intro::CleanUp()
{
	LOG("Freeing scene intro");
	active = false;
	img = nullptr;
	return true;
}
