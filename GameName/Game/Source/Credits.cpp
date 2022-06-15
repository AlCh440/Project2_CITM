#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Credits.h"
#include "LevelManagement.h"
#include "Ease.h"


#include "Defs.h"
#include "Log.h"

Credits::Credits(bool isActive) : Module(isActive)
{
	name.Create("credits");
	toSave = false;
	saveConfigs = false;
}

// Destructor
Credits::~Credits()
{}

// Called before render is available
bool Credits::Awake()
{
	LOG("Loading Intro Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Credits::Start()
{

	music = music = app->audio->PlayMusic("assets/audio/music/song_menu.wav", 0.5f); // to change
	waitTime = 200;
	img = app->tex->Load("Assets/Sprites/UI/screen_logo.jpg");// change the image
	rect = { 0, 0, 1280, 720 };
	logoXpos = -100;
	return true;
}

// Called each loop iteration
bool Credits::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Credits::Update(float dt)
{

	if (counter < easingTime)
	{

		auto easingFunction = getEasingFunction(EaseOutBounce);
		double progress = easingFunction(UpdateProgress(counter, 0, 100, 0, 1));
		logoXpos = (int)UpdateProgress(progress, 0, 1, -100, 0);
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

	if (SDL_SCANCODE_SPACE == KEY_DOWN)
		app->levelManagement->LoadScene(GameScene::START);

	return true;
}

// Called each loop iteration
bool Credits::PostUpdate()
{

	app->render->DrawTexture(img, logoXpos, 0, &rect, 0, 0, 0, 0, 0.5f);

	return true;
}

// Called before quitting
bool Credits::CleanUp()
{
	LOG("Freeing credits scene");
	active = false;
	img = nullptr;
	return true;
}
