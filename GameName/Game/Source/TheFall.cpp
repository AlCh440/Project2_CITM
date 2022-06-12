#include "TheFall.h"
#include "Log.h"
#include "App.h"
#include "Map.h"
#include "Entities.h"
#include "Audio.h"
#include "Physics.h"
#include "GuiManager.h"
#include "ModuleParticles.h"

TheFall::TheFall(bool isActive) : Module(isActive)
{
	name.Create("The_fall");
	toSave = false;
	saveConfigs = false;
}

TheFall::~TheFall()
{
}

bool TheFall::Awake(pugi::xml_node&)
{
	return true;
}

bool TheFall::Start()
{
	app->levelManagement->inCombat = false;
	music = app->audio->PlayMusic("assets/audio/music/song_1_2.wav", 0);

	app->physics->Start();
	app->map->Load("level1.tmx");
	app->entities->Start();
	
	app->entities->LinkDoors();
	
	app->entities->exitIntance->scene = GameScene::GREEN_PATH;
	
	uncheckableTiles[0] = { 15, 37 };
	uncheckableTiles[1] = { 16, 37 };
	uncheckableTiles[2] = { 17, 37 };


	if (app->entities->openWorld != nullptr)
	{
		app->entities->openWorld->SetPositionFromPixels(app->levelManagement->playerLastPos_TheFall);
	}

	hasBeenCreated = false;

	
	return true;
}

bool TheFall::PreUpdate()
{
	return true;
}

bool TheFall::Update(float dt)
{
	if (app->entities->openWorld != nullptr)
	{
		bool ret = true;
		for (int i = 0; i < 3; i++)
		{
			iPoint toCheck[9] = {
				app->entities->openWorld->GetPositionTiles(),
				{app->entities->openWorld->GetPositionTiles().x,app->entities->openWorld->GetPositionTiles().y - 1},
				{app->entities->openWorld->GetPositionTiles().x + 1,app->entities->openWorld->GetPositionTiles().y - 1},
				{app->entities->openWorld->GetPositionTiles().x + 1,app->entities->openWorld->GetPositionTiles().y},
				{app->entities->openWorld->GetPositionTiles().x + 1,app->entities->openWorld->GetPositionTiles().y + 1},
				{app->entities->openWorld->GetPositionTiles().x,app->entities->openWorld->GetPositionTiles().y + 1},
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
			app->levelManagement->playerLastPos_TheFall = { app->entities->openWorld->GetPosition().x + 16,app->entities->openWorld->GetPosition().y + 16 };
	}
	
	if (app->dialogManager->dialog_intro.Finished())
	{
		if (hasBeenCreated == false)
		{
			app->guiManager->OpenPanel(P_QUEST);
			hasBeenCreated = true;
		}
		
	}

	if (app->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN)
	{
		hasBeenCreated = !hasBeenCreated;
	}

	//leaf particles
	if (app->RandomRange(0, 3) == 3)
	{

		Particle* p = app->particles->AddParticle(app->particles->leaf,
			app->RandomRange(
				-app->render->camera.x - app->win->GetWidth() / 2,
				-app->render->camera.x + app->win->GetWidth() / 2),
			-app->render->camera.y / app->win->GetScale() - 10);

		p->speed = fPoint(app->RandomRange(0.01f, -0.01f), app->RandomRange(0.1f, .3f));
		p->accel = fPoint(app->RandomRange(0.02f, -0.02f), app->RandomRange(0.f, 0.03f));
		p->anim.speed = app->RandomRange(0.01f, 0.1f);

	}

	//spark particles
	if (app->RandomRange(0, 20) == 1)
	{
		fPoint p_pos = { (float)app->entities->exitIntance->GetPosition().x, (float)app->entities->exitIntance->GetPosition().y };
		float p_offset_x = app->entities->exitIntance->physBody->width;
		float p_offset_y = app->entities->exitIntance->physBody->height;

		Particle* p = app->particles->AddParticle(app->particles->spark,
			64 + 32 + app->RandomRange(p_pos.x + p_offset_x/2, p_pos.x - p_offset_x/2),
			16 + app->RandomRange(p_pos.y + p_offset_y/2, p_pos.y - p_offset_y/2));

		p->speed = fPoint(app->RandomRange(0.01f, -0.01f), app->RandomRange(0.01f, -0.01f));
		p->anim.speed = app->RandomRange(0.1f, 0.17f);
	}

	
	

	

	return true;
}

bool TheFall::PostUpdate()
{
	iPoint toCheck[9] = {
				app->entities->openWorld->GetPositionTiles(),
				{app->entities->openWorld->GetPositionTiles().x,app->entities->openWorld->GetPositionTiles().y - 1},
				{app->entities->openWorld->GetPositionTiles().x + 1,app->entities->openWorld->GetPositionTiles().y - 1},
				{app->entities->openWorld->GetPositionTiles().x + 1,app->entities->openWorld->GetPositionTiles().y},
				{app->entities->openWorld->GetPositionTiles().x + 1,app->entities->openWorld->GetPositionTiles().y + 1},
				{app->entities->openWorld->GetPositionTiles().x,app->entities->openWorld->GetPositionTiles().y + 1},
				{app->entities->openWorld->GetPositionTiles().x - 1,app->entities->openWorld->GetPositionTiles().y + 1},
				{app->entities->openWorld->GetPositionTiles().x - 1,app->entities->openWorld->GetPositionTiles().y},
				{app->entities->openWorld->GetPositionTiles().x - 1,app->entities->openWorld->GetPositionTiles().y - 1}
	};

	for (size_t i = 1; i < 9; i++)
	{
		SDL_Rect r = { toCheck[i].x * 32 ,toCheck[i].y * 32,32,32 };
		app->render->DrawRectangle(r, 255, 0, 0, 100, true);

	}
	SDL_Rect r = { toCheck[0].x * 32 ,toCheck[0].y * 32,32,32 };
	app->render->DrawRectangle(r, 128, 0, 0, 100, true);

	app->map->Draw();
	
	return true;
}

bool TheFall::CleanUp()
{
	app->map->CleanUp();
	app->entities->CleanUp();
	//app->physics->CleanUp();
	app->audio->StopMusic();
	return true;
}

