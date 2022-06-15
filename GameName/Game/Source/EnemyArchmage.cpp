#include "EnemyArchmage.h"

#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Enemy.h"
#include "Entities.h"
#include "Player.h"
#include "Physics.h"
#include "Pathfinding.h"
#include "ModuleParticles.h"

#include "Log.h"

EnemyArchmage::EnemyArchmage(iPoint pos) : Enemy(pos)
{
	texture = app->tex->Load("Assets/Sprites/characters/archmage_spritesheet.png");	
	physBody = app->physics->CreateCircle(pos.x, pos.y, 16.0f, b2_dynamicBody);
	physBody->entityPtr = this;
	physBody->body->SetGravityScale(0);

	stats.hp = 10;

}

EnemyArchmage::EnemyArchmage(Collider_Type type, iPoint pos) : Enemy(type, pos)
{

	name.Create("Archmage");
	texture = app->tex->Load("Assets/Sprites/characters/archmage_spritesheet.png");
	physBody = app->physics->CreateCircle(pos.x, pos.y, 32.f * 0.5f, b2_dynamicBody);
	physBody->entityPtr = this;
	physBody->body->SetGravityScale(0);
	
	stats.hp = 35;
	stats.movement = 2;
	stats.baseDamage = 11;
	moveTime = 32; //milisec
	counter = moveTime;
	moveRange = 5;
	Start();
}


void EnemyArchmage::UpdatePath()
{
}

bool EnemyArchmage::Start()
{
	tileMove = app->audio->LoadFx("Assets/audio/fx/battleTileMovement.wav");
	mummyDeath = app->audio->LoadFx("Assets/audio/fx/mummyDeath.wav");
	mummyAttack = app->audio->LoadFx("Assets/audio/fx/magic_attack.wav");

	stepCounter = 0;
	moveRange = 5;
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


	inter_speed = 0.02f;
	float movSpeed = 0.07;

	idle.PushBack({ 0, 256, 40, 40 });
	idle.PushBack({ 40, 256, 40, 40 });
	idle.speed = 0.03f;
	idle.loop = true;

	walkSide.PushBack({ 40 * 7, 256, 40, 40 });
	walkSide.PushBack({ 40 * 8, 256, 40, 40 });
	walkSide.PushBack({ 40 * 9, 256, 40, 40 });
	walkSide.PushBack({ 40 * 9, 256, 40, 40 });
	walkSide.pingpong = true;
	walkSide.speed = movSpeed;
	walkSide.loop = true;

	walkUp.PushBack({ 40 * 7, 256, 40, 40 });
	walkUp.PushBack({ 40 * 8, 256, 40, 40 });
	walkUp.PushBack({ 40 * 9, 256, 40, 40 });
	walkUp.pingpong = true;
	walkUp.speed = movSpeed;
	walkUp.loop = true;

	walkDown.PushBack({ 40 * 7, 256, 40, 40 });
	walkDown.PushBack({ 40 * 8, 256, 40, 40 }); 
	walkDown.PushBack({ 40 * 9, 256, 40, 40 });
	walkDown.pingpong = true;
	walkDown.speed = movSpeed;
	walkDown.loop = true;

	dead.PushBack({ 40 * 6, 256, 40, 40 });
	dead.loop = false;
	dead.speed = 0.3f;

	hit.PushBack({ 40 * 10, 256, 40, 40 });
	hit.PushBack({ 40 * 10, 256, 40, 40 });
	hit.loop = false;
	hit.speed = 0.2f;

	attack.PushBack({ 40 * 0, 256, 40, 40 });
	attack.PushBack({ 40 * 1, 256, 40, 40 });
	attack.PushBack({ 40 * 0, 256, 40, 40 });
	attack.PushBack({ 40 * 1, 256, 40, 40 });
	attack.loop = false;
	attack.speed = 0.1f;

	/*for(int i = 0; i < 21; i++)
	{
		if (i <= 7)
		{
			idle.PushBack({ 48 * i, 48 * 3, 48, 48 });
			idle.speed = 0.1f;
			idle.loop = true;
			walkSide.PushBack({ 48 * i, 48 * 3, 48, 48 });
			walkSide.speed = 0.1f;
			walkSide.loop = true;
			walkDown.PushBack({ 48 * i, 48 * 3, 48, 48 });
			walkDown.speed = 0.1f;
			walkDown.loop = true;
			walkUp.PushBack({ 48 * i, 48 * 3, 48, 48 });
			walkUp.speed = 0.1f;
			walkUp.loop = true;
		}
		else if (i >= 8 && i <= 13)
		{
			dead.PushBack({ 48 * i, 48 * 3, 48, 48 });
			dead.loop = false;
			dead.speed = 0.3f;
		}
		else if (i >= 14 && i <= 16)
		{
			hit.PushBack({ 48 * i, 48 * 3, 48, 48 });
			hit.loop = false;
			hit.speed = 0.2f;
		}
		else if (i <= 17)
		{
			attack.PushBack({ 48 * i, 48 * 3, 48, 48 });
			attack.loop = false;
			attack.speed = 0.1f;
		}
	}*/


	inter_speed = 0.02f;

	currentAnim = &idle;

	return true;
}

bool EnemyArchmage::PreUpdate()
{


	switch (battleState)
	{
	case IDLE:
	{
		//store the entity position in tiles
		iPoint pos;
		pos.x = position.x;
		pos.y = position.y;
		pos = app->map->WorldToMap(pos.x, pos.y);

		tilePos = pos;

		if (OnHit)
			currentAnim = &hit;

		if (entityTurn)
		{

			if (battleState == DEATH)
				break;
			if (target == nullptr)
			{

				p2ListItem<Player*>* p = app->entities->GetNearestPlayer(this);
				while(p != nullptr)
				{
					if (p->data->battleState == DEATH)
					{
						target = nullptr;
					}
					else {
						target = p->data;
						break;
					}

					p = p->next;
				}
			}
			else {
				
				if ( HasAttackAction &&  pathfinding->CreatePath(tilePos, target->tilePos ) <=  6)
				{
					battleState = ATTACK;
					attack.Reset();
					currentAnim = &attack;
					HasMoveAction = false;
				}
				else if (HasMoveAction)
				{
					battleState = MOVE;
					currentAnim = &idle;
				}
				else 
				{
					// if has mmoved and has no range then, has no attack action
					HasAttackAction = false;
				}
			}
		}
		//if has no attack and no move action end turn
		if (!HasAttackAction && !HasMoveAction) {
			entityTurn = false;
		}

	}
		break;
	case MOVE:
		//Search for new pos
		break;
	case ATTACK:
		//Search for target
		break;
	case DEATH:
		break;
	default:
		break;
	}
	return true;
}

bool EnemyArchmage::Update(float dt)
{	
	switch (battleState)
	{
	case IDLE:
		//Nothing to do
		if(OnHit)
		{
			if (currentAnim->HasFinished()) {
				OnHit = false;
				hit.Reset();
				currentAnim = &idle;
			}
		}
		break;
	case MOVE:
		if (timer > 0) timer--;
		else
		{
			timer = timerRef;
			app->audio->PlayFx(tileMove,0 );
		}
	
		
		if (!Move) {

			//Set available movement tiles
			if (!NewTarget)
			{
				pathfinding->InitBFS(tilePos);
				for (int i = 0; i < 50; i++)
				{
					pathfinding->PropagateBFS();
				}
				
				//pathfinding->GenerateWalkeableArea(tilePos, 100);


				
				if (InitPath(target->tilePos)) {
					NewTarget = true;
				}
				else {
					entityTurn = false;
				}
				
			}
		}

		if (MovePath()) {
			NewTarget = false;
			target = nullptr;
			currentAnim = &idle;
		}
		break;
	case ATTACK:
		//Search for target
		
		if (target != nullptr && currentAnim->HasFinished())
		{
			target->takeDamage(stats.baseDamage);
			HasAttackAction = false;
			currentAnim = &idle;
			battleState = IDLE;

			for (int i = 0; i < app->RandomRange(5,20); i++)
			{
				fPoint p_pos = { (float)target->GetPosition().x + 12, (float)target->GetPosition().y + 12};
				float p_offset_x = 0;
				float p_offset_y = 0;

				Particle* p = app->particles->AddParticle(app->particles->archmage_spark,
					 app->RandomRange(p_pos.x + p_offset_x / 2, p_pos.x - p_offset_x / 2),
					app->RandomRange(p_pos.y + p_offset_y / 2, p_pos.y - p_offset_y / 2));

				p->speed = fPoint(app->RandomRange(0.2f, -0.4f), app->RandomRange(0.2f, -0.4f));
				p->anim.speed = app->RandomRange(0.1f, 0.17f);
			}

			app->audio->PlayFx(mummyAttack);
		}
		break;
	case DEATH:
		
		break;
	default:
		break;
	}

	currentAnim->Update();
	return true;
}

bool EnemyArchmage::PostUpdate()
{
	//render current tile pos
	SDL_Rect r;
	r.x = position.x - app->map->mapData.tileWidth * .5f;
	r.y = position.y - app->map->mapData.tileHeight * .5f;
	r.w = app->map->mapData.tileWidth;
	r.h = app->map->mapData.tileHeight;

	app->render->DrawRectangle(r, 255, 100, 255, 150, true);
	switch (battleState)
	{
	case IDLE:
		//Nothing to do
		break;
	case MOVE:
	{
		//draw movement area
		pathfinding->DrawBFSPath();
		//Search for new pos//Draw path
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
				app->render->DrawRectangle(rect, 255, 125, 125, 150);
			}
		}
	}
		break;
	case ATTACK:
		//Search for target
		break;
	case DEATH:
		break;
	default:
		break;
	}
	
	//render entity
	app->render->DrawTexture(texture, position.x - 24 + 8, position.y - 32 + 8, &currentAnim->GetCurrentFrame());

	return true;
}

bool EnemyArchmage::CleanUp()
{
	physBody->pendingToDelete = true;
	
	return true;
}

bool EnemyArchmage::BasicAttack() // pass an Player
{
	return true;
}

// 
void EnemyArchmage::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

}

// Load / Save
bool EnemyArchmage::LoadState(pugi::xml_node& data)
{
	return true;
}

bool EnemyArchmage::SaveState(pugi::xml_node& data) const
{
	return true;
}