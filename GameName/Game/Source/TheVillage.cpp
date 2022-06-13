#include "TheVillage.h"
#include "Log.h"
#include "App.h"
#include "Map.h"
#include "Entities.h"
#include "Audio.h"
#include "Physics.h"
#include "ModuleParticles.h"

TheVillage::TheVillage(bool isActive) : Module(isActive)
{
	name.Create("The_Village");
	toSave = false;
	saveConfigs = false;
}

TheVillage::~TheVillage()
{
}

bool TheVillage::Awake(pugi::xml_node&)
{
	return true;
}

bool TheVillage::Start()
{
	app->levelManagement->inCombat = false;
	music = app->audio->PlayMusic("assets/audio/music/village.wav", 0);
	app->physics->Start();
	app->map->Load("level3.tmx");
	app->entities->Start();
	app->entities->exitIntance->scene = GameScene::RUINS;
	app->entities->entranceIntance->scene = GameScene::GREEN_PATH;

	app->entities->generalEntrance->scene= GameScene::GENERAL_ROOM;
	app->entities->mageEntrance->scene = GameScene::MAGE_ROOM;
	app->entities->shopEntrance->scene = GameScene::SHOP_ROOM;
	app->entities->LinkDoors();
	if (app->entities->openWorld != nullptr)
	{
		if (app->loadingScreen == false)
		{
			app->entities->openWorld->SetPositionFromPixels(app->levelManagement->playerLastPos_Village);
		}
		else
		{
			app->loadingScreen = false;
		}
	}

	//entrance
	uncheckableTiles[0] = { 14, 8 };
	uncheckableTiles[1] = { 14, 9 };
	uncheckableTiles[2] = { 14, 10 };

	//exit
	uncheckableTiles[3] = { 90, 36 };
	uncheckableTiles[4] = { 90, 37 };
	uncheckableTiles[5] = { 90, 33 };
	uncheckableTiles[6] = { 90, 39 };
	//rooms
	uncheckableTiles[7] = { 59, 15 };
	uncheckableTiles[8] = { 73, 36 };
	uncheckableTiles[9] = { 79, 36 };

	//enemy triggers
	uncheckableTiles[10] = { 27, 38 };
	uncheckableTiles[11] = { 32, 36 };
	uncheckableTiles[12] = { 35, 42 };
	uncheckableTiles[13] = { 19, 80 };
	uncheckableTiles[14] = { 24, 81 };
	uncheckableTiles[15] = { 18, 84 };
	uncheckableTiles[16] = { 21, 89 };
	uncheckableTiles[17] = { 24, 89 };
	uncheckableTiles[18] = { 27, 84 };

	return true;
}

bool TheVillage::PreUpdate()
{
	return true;
}

bool TheVillage::Update(float dt)
{
	if (app->entities->openWorld != nullptr)
	{
		bool ret = true;
		for (int i = 0; i < 19; i++)
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
			app->levelManagement->playerLastPos_Village = { app->entities->openWorld->GetPosition().x + 16,app->entities->openWorld->GetPosition().y + 16 };
	}


	if (app->RandomRange(0, 15) == 1)
	{
		fPoint p_pos = { (float)app->entities->exitIntance->GetPosition().x, (float)app->entities->exitIntance->GetPosition().y };
		float p_offset_x = app->entities->exitIntance->physBody->width;
		float p_offset_y = app->entities->exitIntance->physBody->height;

		Particle* p = app->particles->AddParticle(app->particles->spark,
			64 + app->RandomRange(p_pos.x + p_offset_x / 2, p_pos.x - p_offset_x / 2),
			16 + 32 + app->RandomRange(p_pos.y + p_offset_y / 2, p_pos.y - p_offset_y / 2));

		p->speed = fPoint(app->RandomRange(0.01f, -0.01f), app->RandomRange(0.01f, -0.01f));
		p->anim.speed = app->RandomRange(0.1f, 0.17f);
	}

	if (app->RandomRange(0, 20) == 1)
	{
		fPoint p_pos = { (float)app->entities->entranceIntance->GetPosition().x, (float)app->entities->entranceIntance->GetPosition().y };
		float p_offset_x = app->entities->entranceIntance->physBody->width;
		float p_offset_y = app->entities->entranceIntance->physBody->height;

		Particle* p = app->particles->AddParticle(app->particles->spark,
		16 + app->RandomRange(p_pos.x + p_offset_x / 2, p_pos.x - p_offset_x / 2),
			64 + 32 + app->RandomRange(p_pos.y + p_offset_y / 2, p_pos.y - p_offset_y / 2));

		p->speed = fPoint(app->RandomRange(0.01f, -0.01f), app->RandomRange(0.01f, -0.01f));
		p->anim.speed = app->RandomRange(0.1f, 0.17f);
	}
	return true;
}

bool TheVillage::PostUpdate()
{
	app->map->Draw();
	return true;
}

bool TheVillage::CleanUp()
{
	app->map->CleanUp();
	app->entities->CleanUp();
	//app->physics->CleanUp();
	app->audio->StopMusic();
	return true;
}
