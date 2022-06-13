#include "TheRuins.h"
#include "Log.h"
#include "App.h"
#include "Map.h"
#include "Entities.h"
#include "Audio.h"
#include "Physics.h"
#include "ModuleParticles.h"
TheRuins::TheRuins(bool isActive) : Module(isActive)
{
	name.Create("The_Ruins");
	toSave = false;
	saveConfigs = false;
}

TheRuins::~TheRuins()
{
}

bool TheRuins::Awake(pugi::xml_node&)
{
	return true;
}

bool TheRuins::Start()
{
	app->levelManagement->inCombat = false;
	music = app->audio->PlayMusic("assets/audio/music/song_1_2.wav", 0);

	app->physics->Start();
	app->map->Load("level4.tmx");
	app->entities->Start();
	app->entities->exitIntance->scene = GameScene::FRACTURED_ROAD;
	app->entities->entranceIntance->scene = GameScene::VILLAGE;
	app->entities->LinkDoors();
	if (app->entities->openWorld != nullptr)
	{
		if (app->loadingScreen == false)
		{
			app->entities->openWorld->SetPositionFromPixels(app->levelManagement->playerLastPos_TheRuins);
		}
		else
		{
			app->loadingScreen = false;
		}
	}
	
	return true;
}

bool TheRuins::PreUpdate()
{
	return true;
}

bool TheRuins::Update(float dt)
{

	if (app->RandomRange(0, 20) == 1)
	{
		fPoint p_pos = { (float)app->entities->exitIntance->GetPosition().x, (float)app->entities->exitIntance->GetPosition().y };
		float p_offset_x = app->entities->exitIntance->physBody->width;
		float p_offset_y = app->entities->exitIntance->physBody->height;

		Particle* p = app->particles->AddParticle(app->particles->spark,
			16 + app->RandomRange(p_pos.x + p_offset_x / 2, p_pos.x - p_offset_x / 2),
			64 + 32 + app->RandomRange(p_pos.y + p_offset_y / 2, p_pos.y - p_offset_y / 2));

		p->speed = fPoint(app->RandomRange(0.01f, -0.01f), app->RandomRange(0.01f, -0.01f));
		p->anim.speed = app->RandomRange(0.1f, 0.17f);
	}
	return true;
}

bool TheRuins::PostUpdate()
{
	app->map->Draw();
	
	
	return true;
}

bool TheRuins::CleanUp()
{
	app->map->CleanUp();
	app->entities->CleanUp();
	//app->physics->CleanUp();
	app->audio->StopMusic();

	return true;
}
