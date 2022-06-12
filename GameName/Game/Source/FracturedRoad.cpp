#include "FracturedRoad.h"
#include "Log.h"
#include "App.h"
#include "Map.h"
#include "Entities.h"
#include "Audio.h"
#include "Physics.h"
#include "ModuleParticles.h"

FracturedRoad::FracturedRoad(bool isActive) : Module(isActive)
{
	name.Create("Fractured_Road");
	toSave = false;
	saveConfigs = false;
}

FracturedRoad::~FracturedRoad()
{
}

bool FracturedRoad::Awake(pugi::xml_node&)
{
	return true;
}

bool FracturedRoad::Start()
{
	music = app->audio->PlayMusic("assets/audio/music/song_1_2.wav", 0);
	app->levelManagement->inCombat = false;
	app->physics->Start();
	app->map->Load("level5.tmx");
	app->entities->Start();
	app->entities->exitIntance->scene = GameScene::DRAGON_CLIFF;
	app->entities->entranceIntance->scene = GameScene::RUINS;
	app->entities->LinkDoors();
	if (app->entities->openWorld != nullptr)
	{
		app->entities->openWorld->SetPositionFromPixels(app->levelManagement->playerLastPos_FracturedRoad);
	}
	return true;
}

bool FracturedRoad::PreUpdate()
{
	return true;
}

bool FracturedRoad::Update(float dt)
{

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

	if (app->RandomRange(0, 20) == 1)
	{
		fPoint p_pos = { (float)app->entities->exitIntance->GetPosition().x, (float)app->entities->exitIntance->GetPosition().y };
		float p_offset_x = app->entities->exitIntance->physBody->width;
		float p_offset_y = app->entities->exitIntance->physBody->height;

		Particle* p = app->particles->AddParticle(app->particles->spark,
			64 + 32 + app->RandomRange(p_pos.x + p_offset_x / 2, p_pos.x - p_offset_x / 2),
			16 + app->RandomRange(p_pos.y + p_offset_y / 2, p_pos.y - p_offset_y / 2));

		p->speed = fPoint(app->RandomRange(0.01f, -0.01f), app->RandomRange(0.01f, -0.01f));
		p->anim.speed = app->RandomRange(0.1f, 0.17f);
	}
	return true;
}

bool FracturedRoad::PostUpdate()
{

	app->map->Draw();
	return true;
}

bool FracturedRoad::CleanUp()
{

	app->map->CleanUp();
	app->entities->CleanUp();
	//app->physics->CleanUp();
	app->audio->StopMusic();
	return true;
}
