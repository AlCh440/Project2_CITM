#include "GreenPath.h"
#include "Log.h"
#include "App.h"
#include "Map.h"
#include "Entities.h"
#include "Audio.h"
#include "Physics.h"
#include "GuiManager.h"

GreenPath::GreenPath(bool isActive) : Module(isActive)
{
	name.Create("Green_path");
	toSave = false;
	saveConfigs = false;
}

GreenPath::~GreenPath()
{
}

bool GreenPath::Awake(pugi::xml_node&)
{
	return true;
}

bool GreenPath::Start()
{
	app->levelManagement->inCombat = false;
	music = app->audio->PlayMusic("assets/audio/music/song_1_2.wav", 0);
	app->physics->Start();
	app->map->Load("level2.tmx");
	//app->entities->Start();
	app->entities->exitIntance->scene = GameScene::VILLAGE;
	app->entities->entranceIntance->scene = GameScene::THE_FALL;

	if (app->entities->openWorld != nullptr)
	{
		app->entities->openWorld->SetPositionFromPixels(app->levelManagement->playerLastPos_GreenPath);
	}
	//entrances
	uncheckableTiles[0] = { 10, 11 };
	uncheckableTiles[1] = { 11, 11 };
	uncheckableTiles[2] = { 12, 11 };
	//exits
	uncheckableTiles[3] = { 100, 20 };
	uncheckableTiles[4] = { 100, 21 };
	uncheckableTiles[5] = { 100, 22 };

	//enemy triggers
	uncheckableTiles[6] = { 28, 20 };
	uncheckableTiles[7] = { 48, 34 };
	uncheckableTiles[8] = { 90, 19 };


	//app->guiManager->OpenPanel(P_QUEST);

	return true;
}

bool GreenPath::PreUpdate()
{
	return true;
}

bool GreenPath::Update(float dt)
{
	if (app->entities->openWorld != nullptr)
	{
		bool ret = true;
		for (int i = 0; i < 9; i++)
		{
			iPoint toCheck[9] = {
				app->entities->openWorld->GetPositionTiles(),
				{app->entities->openWorld->GetPositionTiles().x, app->entities->openWorld->GetPositionTiles().y - 1},
				{app->entities->openWorld->GetPositionTiles().x + 1,app->entities->openWorld->GetPositionTiles().y - 1},
				{app->entities->openWorld->GetPositionTiles().x + 1,app->entities->openWorld->GetPositionTiles().y},
				{app->entities->openWorld->GetPositionTiles().x + 1,app->entities->openWorld->GetPositionTiles().y + 1},
				{app->entities->openWorld->GetPositionTiles().x, app->entities->openWorld->GetPositionTiles().y + 1},
				{app->entities->openWorld->GetPositionTiles().x - 1,app->entities->openWorld->GetPositionTiles().y + 1},
				{app->entities->openWorld->GetPositionTiles().x - 1,app->entities->openWorld->GetPositionTiles().y},
				{app->entities->openWorld->GetPositionTiles().x - 1,app->entities->openWorld->GetPositionTiles().y - 1}
			};

			for (size_t j = 0; j < 9; j++)
			{
				if (toCheck[j] == uncheckableTiles[i])
				{
					ret = false;
					break;
				}
			}
		}

		if (ret == true)
			app->levelManagement->playerLastPos_GreenPath = { app->entities->openWorld->GetPosition().x, app->entities->openWorld->GetPosition().y };

	}


	return true;
}

bool GreenPath::PostUpdate()
{
	app->map->Draw();
	return true;
}

bool GreenPath::CleanUp()
{
	app->map->CleanUp();
	app->entities->CleanUp();
	//app->physics->CleanUp();
	app->audio->StopMusic();
	return true;
}
