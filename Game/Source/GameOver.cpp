#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "GameOver.h"
#include "LevelManagement.h"
#include "ModulePhysics.h"
#include "player.h"

#include "Defs.h"
#include "Log.h"

GameOver::GameOver(bool isActive) : Module(isActive)
{
	name.Create("game_over");
}

// Destructor
GameOver::~GameOver()
{}

// Called before render is available
bool GameOver::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool GameOver::Start()
{
	img = app->tex->Load("Assets/Spritesx16/GameOver.png");

	menuPanel = new GuiPanel(true);
	menuPanel->bounds = { 0,0,0,0 };
	menuPanel->position = { 0,0 };
	backToTitleButton = (GuiButton*)menuPanel->CreateGuiControl(GuiControlType::BUTTON, 5, "backtotitle", 0, { (app->win->GetWidth() / 2) - 85 , (app->win->GetHeight() / 2), 170, 60 }, this);
	backToTitleButton->texture = app->guiManager->UItexture;
	backToTitleButton->normalRec = { 340,120,170,60 };
	backToTitleButton->focusedRec = { 340,180,170,60 };

	return true;
}

// Called each loop iteration
bool GameOver::PreUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called each loop iteration
bool GameOver::Update(float dt)
{
	rect.x = 0;
	rect.y = 0;
	rect.w = 1280;
	rect.h = 480;
	if (img != nullptr && active)
		app->render->DrawTexture(img, 0, 0, &rect, 1.0f, 0.0f, 1, 1, 1, SDL_FLIP_NONE);

	menuPanel->Update(dt);
	return true;
}

// Called each loop iteration
bool GameOver::PostUpdate()
{
	bool ret = true;

	menuPanel->Draw();

	return ret;
}

// Called before quitting
bool GameOver::CleanUp()
{
	LOG("Freeing scene gameover");
	active = false;
	img = nullptr;
	return true;
}

bool GameOver::OnGuiMouseClickEvent(GuiControl* control)
{
	if (control->id == backToTitleButton->id)
	{
		app->levelManagement->gameState = app->levelManagement->START;
	}
	return true;
}
