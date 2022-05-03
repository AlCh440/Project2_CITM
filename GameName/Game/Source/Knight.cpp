#include "Knight.h"
#include "Defs.h"
#include "App.h"
#include "Audio.h"
#include "Input.h"
#include "Entities.h"
#include "Physics.h"
#include "LevelManagement.h"
#include "Render.h"
#include "Map.h"
#include "Log.h"
#include "Player.h"

// Update Code
Knight::Knight(Collider_Type type, iPoint pos) : Player(type, pos)
{
	texture = app->tex->Load("Assets/Sprites/characters/charactersSpritesheet.png");
	physBody = app->physics->CreateCircle(pos.x, pos.y, 32.f * 0.5f, b2_dynamicBody);
	physBody->body->SetGravityScale(0);
	physBody->entityPtr = this;
	stats.hp = 100;
	stats.mana = 50;
	stats.movement = 10;
	typeOfPlayer = 1;
	actionPoints = 10; // To determine
	isAlive = true;
	//state = COMBATMOVE;
	moveTime = 32; //milisec
	counter = moveTime;
}

bool Knight::Start()
{

	stats.hp = 100;
	stats.mana = 50;
	stats.movement = 10;
	typeOfPlayer = 1;
	actionPoints = 10; // To determine
	isAlive = true;
	stepCounter = 0;
	moveRange = 5;

	direction = new iPoint{ 0, 0 };

	walkSide.PushBack({0, 0, 32, 48});
	walkSide.PushBack({32, 0, 32, 48});
	walkSide.PushBack({64, 0, 32, 48});
	walkSide.PushBack({96, 0, 32, 48});
	walkSide.loop = true;
	walkSide.speed = 0.1f;
	

	walkDown.PushBack({ 0, 48, 32, 48 });
	walkDown.PushBack({ 32, 48, 32, 48 });
	walkDown.PushBack({ 64, 48, 32, 48 });
	walkDown.PushBack({ 96, 48, 32, 48 });
	walkDown.loop = true;
	walkDown.speed = 0.1f;


	walkUp.PushBack({ 0, 96, 32, 48 });
	walkUp.PushBack({ 32, 96, 32, 48 });
	walkUp.PushBack({ 64, 96, 32, 48 });
	walkUp.PushBack({ 96, 96, 32, 48 });
	walkUp.loop = true;
	walkUp.speed = 0.1f;

	currentAnim = &walkDown;

	pathfinding = new PathFinding(true);
	//create navigation map
	int w, h;
	uchar* data = NULL;
	if (app->map->CreateWalkabilityMap(w, h, &data, 1)) pathfinding->SetMap(w, h, data);
	RELEASE_ARRAY(data);

	//store the entity position in tiles
	iPoint pos;
	pos.x = position.x;
	pos.y = position.y;
	pos = app->map->WorldToMap(pos.x, pos.y);

	tilePos = pos;

	pathfinding->InitBFS(tilePos);
	for (int i = 0; i < stats.movement * moveRange; i++)
		pathfinding->PropagateBFS();

	

	return true;
}

bool Knight::PreUpdate()
{

	if(app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
	{
		entityTurn = false;
	}


	switch (battleState)
	{
	case IDLE:
		//nothing to do
		break;
	case MOVE:
		//Select tile to move to
		if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_DOWN && !Move && ExpandedBFS) {
			int x, y;
			app->input->GetMouseWorldPosition(x, y);
			iPoint p;
			p.x = x;
			p.y = y;
			p = app->map->WorldToMap(p.x, p.y);

			InitPath(p);
		}
		break;
	case ATTACK:
		break;
	case DEATH:
		break;
	default:
		break;
	}


	return true;
}

bool Knight::Update(float dt)
{
	switch (battleState)
	{
	case IDLE:
		//update idle
		break;
	case MOVE:
		
		//Expand tiles to available
		 if(!ExpandedBFS){

			pathfinding->ResetBFSPath();
			iPoint mapPos;
			mapPos = app->map->WorldToMap(position.x, position.y);

			pathfinding->InitBFS(mapPos);

			for (int i = 0; i < stats.movement * 4 + 1; i++)
				pathfinding->PropagateBFS();

			ExpandedBFS = true;
		 }

		//move
		MovePath();

		if(currentAnim != NULL)
			currentAnim->Update();

		break;
	case ATTACK:
		break;
	case DEATH:
		break;
	default:
		break;
	}
	return true;
}

bool Knight::PostUpdate()
{
	SDL_Rect r;

	switch (battleState)
	{
	case IDLE:
		//render idle 
		break;
	case MOVE:
	{//draw movement
		pathfinding->DrawBFSPath();

		//Draw path
		const DynArray<iPoint>* path = pathfinding->GetLastPath();

		SDL_Rect rect;
		for (uint i = 0; i < path->Count(); ++i)
		{
			iPoint pos = app->map->MapToWorld(path->At(i)->x, path->At(i)->y);
			rect.x = (pos.x);
			rect.y = (pos.y);
			rect.w = (app->map->mapData.tileWidth);
			rect.h = (app->map->mapData.tileHeight);
			app->render->DrawRectangle(rect, 255, 125, 0, 150);
		}
	}
		break;
	case ATTACK:
		break;
	case DEATH:
		break;
	default:
		break;
	}





	if (direction->x <= 0)
	{
		app->render->DrawTexture(texture, position.x - 20, position.y -30, &currentAnim->GetCurrentFrame());
	}
	else
	{
		app->render->DrawTexture(texture, position.x - 20, position.y -30, &currentAnim->GetCurrentFrame(), 1.0f, 0.0f, 2147483647, 2147483647, 1.0f, SDL_FLIP_HORIZONTAL);
	}




	int x, y;

	app->input->GetMouseWorldPosition(x, y);
	iPoint p;
	p.x = x;
	p.y = y;
	p = app->map->WorldToMap(p.x, p.y);
	p = app->map->MapToWorld(p.x, p.y);

	r.x = p.x;
	r.y = p.y;
	r.w = app->map->mapData.tileWidth;
	r.h = app->map->mapData.tileHeight;

	app->render->DrawRectangle(r, 125, 255, 255, 150, true);

	r.x = position.x - app->map->mapData.tileWidth * .5f;
	r.y = position.y - app->map->mapData.tileHeight * .5f ;
	r.w = app->map->mapData.tileWidth;
	r.h = app->map->mapData.tileHeight;

	app->render->DrawRectangle(r, 125, 255, 0, 150, true);

	return true;
}

bool Knight::CleanUp()
{
	// destroy the physbody

	return true;
}

bool Knight::BasicAttack() // pass an ennemy
{


	return true;
}

bool Knight::TauntHability()
{


	return true;
}

bool Knight::BindHability()
{


	return true;
}

bool Knight::ConcusionHability(PhysBody* tarjet)
{
	tarjet->entityPtr->takeDamage(20);

	return true;
}

// OnCollision
void Knight::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

}

// Load / Save
bool Knight::LoadState(pugi::xml_node& data) 
{


	return true;
}

bool Knight::SaveState(pugi::xml_node& data) const
{


	return true;
}