#include "Ranger.h"
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
Ranger::Ranger(Collider_Type type, iPoint pos) : Player(type, pos)
{
	physBody = app->physics->CreateCircle(pos.x, pos.y, 32.f * 0.5f, b2_dynamicBody);
	physBody->body->SetGravityScale(0);
	physBody->entityPtr = this;
	texture = app->tex->Load("Assets/Sprites/characters/charactersSpritesheet.png");
}

Ranger::~Ranger()
{
}

bool Ranger::Start()
{
	attack = app->audio->LoadFx("Assets/audio/fx/swoosh.wav");

	stats.hp = 75;
	stats.mana = 75;
	stats.movement = 5;
	stats.attackRange = 3;
	stats.baseDamage = 15;
	typeOfPlayer = 2;
	actionPoints = 10; // To determine
	isAlive = true;

	typeOfPlayer = 1;
	actionPoints = 10; // To determine
	isAlive = true;
	stepCounter = 0;
	moveRange = 2;
	counter = moveTime;

	HasMoveAction = true;
	HasAttackAction = true;

	direction = new iPoint{ 0, 0 };

	walkSide.PushBack({ 128, 0, 32, 48 });
	walkSide.PushBack({ 160, 0, 32, 48 });
	walkSide.PushBack({ 192, 0, 32, 48 });
	walkSide.PushBack({ 224, 0, 32, 48 });
	walkSide.loop = true;
	walkSide.speed = 0.1f;


	walkDown.PushBack({ 128, 48, 32, 48 });
	walkDown.PushBack({ 160, 48, 32, 48 });
	walkDown.PushBack({ 192, 48, 32, 48 });
	walkDown.PushBack({ 224, 48, 32, 48 });
	walkDown.loop = true;
	walkDown.speed = 0.1f;


	walkUp.PushBack({ 128, 96, 32, 48 });
	walkUp.PushBack({ 160, 96, 32, 48 });
	walkUp.PushBack({ 192, 96, 32, 48 });
	walkUp.PushBack({ 224, 96, 32, 48 });
	walkUp.loop = true;
	walkUp.speed = 0.1f;

	dead.PushBack({});
	dead.loop = false;
	dead.speed = 0.1;

	hit.PushBack({ 128, 96, 32, 48 });
	hit.PushBack({ 160, 96, 32, 48 });
	hit.PushBack({ 192, 96, 32, 48 });
	hit.PushBack({ 224, 96, 32, 48 });
	hit.loop = false;
	hit.speed = 0.1f;

	currentAnim = &walkDown;

	//Load Entity attacks
	Attack* basicAttack = new Attack();
	basicAttack->damage = 2;
	basicAttack->id = 0;

	//attackList->add(basicAttack);


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
	return true;
}

bool Ranger::PreUpdate()
{
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		entityTurn = false;
	}

	switch (battleState)
	{
	case IDLE:
	{
		iPoint pos;
		pos.x = position.x;
		pos.y = position.y;
		pos = app->map->WorldToMap(pos.x, pos.y);
		tilePos = pos;

		ExpandedBFS = false;
	}
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
		//load attack 
		//Expand tiles to available
		if (!ExpandedBFS) {

			switch (attackChoosed)
			{

			default:
				break;
			}
			pathfinding->GenerateInteractionArea(tilePos, stats.attackRange);


			ExpandedBFS = true;
		}
		//Select entity target
		if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_DOWN) {
			int x, y;
			app->input->GetMouseWorldPosition(x, y);
			iPoint p;
			p.x = x;
			p.y = y;
			p = app->map->WorldToMap(p.x, p.y);

			if (pathfinding->IsVisited(p))
			{
				target = app->entities->GetEntityFromTile(p);
				if (target == nullptr)
				{
					battleState = IDLE;
					pathfinding->ResetBFSPath();
				}
				else
				{
					target->takeDamage(stats.baseDamage);
					basicHit.Reset();
					currentHitAnim = &basicHit;
					battleState = IDLE;
					HasAttackAction = false;
				}
			}
			else {
				battleState = IDLE;
				pathfinding->ResetBFSPath();
			}
			app->audio->PlayFx(attack);
		}
		break;
	case DEATH:
		break;
	default:
		break;
	}

	if (currentHitAnim != nullptr && currentHitAnim->HasFinished())
	{
		currentHitAnim = nullptr;
	}

	return true;
}

bool Ranger::Update(float dt)
{
	switch (battleState)
	{
	case IDLE:
		//update idle
		break;
	case MOVE:

		//Expand tiles to available
		if (!ExpandedBFS) {


			pathfinding->GenerateWalkeableArea(tilePos, stats.movement);

			ExpandedBFS = true;
		}

		//move
		MovePath();


		break;
	case ATTACK:

		break;
	case DEATH:
		break;
	default:
		break;
	}

	if (currentHitAnim != NULL)
		currentHitAnim->Update();
	if (currentAnim != NULL)
		currentAnim->Update();

	return true;
}

bool Ranger::PostUpdate()
{
	SDL_Rect r;
	//Entity tile Pos
	r.x = position.x - app->map->mapData.tileWidth * .5f;
	r.y = position.y - app->map->mapData.tileHeight * .5f;
	r.w = app->map->mapData.tileWidth;
	r.h = app->map->mapData.tileHeight;

	app->render->DrawRectangle(r, 125, 255, 0, 150, true);


	switch (battleState)
	{
	case IDLE:
		//render idle 
		break;
	case MOVE:
	{
		//draw movement
		pathfinding->DrawBFSPath();

		//Draw path
		const DynArray<iPoint>* path = pathfinding->GetLastPath();
		if (path != nullptr)
		{
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
	}
	break;
	case ATTACK:
		//draw movement
		pathfinding->DrawBFSPath();
		break;
	case DEATH:
		break;
	default:
		break;
	}


	if (direction->x <= 0)
	{
		app->render->DrawTexture(texture, position.x - 16, position.y - 30, &currentAnim->GetCurrentFrame());
	}
	else
	{
		app->render->DrawTexture(texture, position.x - 16, position.y - 30, &currentAnim->GetCurrentFrame(), 1.0f, 0.0f, 2147483647, 2147483647, 1.0f, SDL_FLIP_HORIZONTAL);
	}

	if (currentHitAnim != nullptr && target != nullptr)
		app->render->DrawTexture(tex_hitfx, target->position.x - 16, target->position.y - 32, &currentHitAnim->GetCurrentFrame());

	return true;
}

bool Ranger::CleanUp()
{
	// destroy the physbody

	return true;
}

// Ranger 

bool Ranger::BasicAttack() // pass an ennemy
{


	return true;
}

bool Ranger::PrecisionShot()
{


	return true;
}

bool Ranger::MultyShot()
{


	return true;
}

bool Ranger::PowerfullStrike()
{


	return true;
}

// OnCollision
void Ranger::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

}

// Load / Save
bool Ranger::LoadState(pugi::xml_node& data)
{


	return true;
}

bool Ranger::SaveState(pugi::xml_node& data) const
{


	return true;
}