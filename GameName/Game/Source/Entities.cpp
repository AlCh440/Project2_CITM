#include "Entities.h"
#include "Point.h"
#include "Log.h"

#include "App.h"
#include "Audio.h"
#include "LevelManagement.h"

#include "Entity.h"

#include "Player.h"
#include "Knight.h"
#include "OpenWorldPlayer.h"

#include "CheckPoint.h"

#include "Enemy.h"
#include "EnemyDummy.h"

#include "Npc.h"
#include "NpcDummy.h"


ModuleEntities::ModuleEntities(bool isActive) : Module(isActive)
{
    name.Create("entities");
    
}

ModuleEntities::~ModuleEntities()
{
}

bool ModuleEntities::Awake()
{
    //test
   
    return true;
}

bool ModuleEntities::Start()
{
    for (p2ListItem<Entity*>* aux = entities.getFirst(); aux != nullptr; aux = aux->next)
    {
        aux->data->Start();
    }

    return true;
}

bool ModuleEntities::PreUpdate()
{
    for (p2ListItem<Entity*>* aux = entities.getFirst(); aux != nullptr; aux = aux->next)
    {
        aux->data->DEBUG = DEBUG;
        aux->data->PreUpdate();

    }

    return true;
}

bool ModuleEntities::Update(float dt)
{
    for (p2ListItem<Entity*>* aux = entities.getFirst(); aux != nullptr; aux = aux->next)
    {
        if (aux->data->entityTurn)
        {
            aux->data->Update(dt);
        }
    }
   
    if (app->levelManagement->gameScene == 11)
    {
        if (app->levelManagement->combatState == PLAYERTURN)
        {
            if (!CheckPlayerTurn())
            {
                StartEnemiesTurn();
            }
        }
        else if (app->levelManagement->combatState == ENEMYTURN)
        {
            if (enemiesAlive <= 0)
            {
                StartPlayerTurn();
            }
        }
    }
    return true;
}

bool ModuleEntities::PostUpdate()
{
    for (p2ListItem<Entity*>* aux = entities.getFirst(); aux != nullptr; aux = aux->next)
    {
        aux->data->PostUpdate();
    }
  
    return true;
}

bool ModuleEntities::CleanUp()
{
    for (p2ListItem<Entity*>* aux = entities.getFirst(); aux != nullptr; aux = aux->next)
    {
        aux->data->Cleanup();
        delete aux->data;
        aux->data = nullptr;
    }
    playerInstance = nullptr;
    knightInstance = nullptr;
    dummyInstance = nullptr;
    dummyNpcInstance = nullptr;
    players.clear();
    entities.clear();
    return true;
}

void ModuleEntities::AddEntity(Collider_Type type, iPoint spawnPos)
{
    switch (type)
    {
    case PLAYER:
         //playerInstance = new Player(type, spawnPos);
         //entities.add(playerInstance);
        break;
    case PLAYERKNIGHT:
        knightInstance = new Knight(type, spawnPos);
        entities.add(knightInstance);
        players.add(knightInstance);
        break;
    case PLAYEROPENWORLD:
    {
        playerInstance = new OpenWorldPlayer(type, spawnPos);
        entities.add(playerInstance);

        // DO NOT ADD TO PLAYERS, PLAYERS LIST IS USED IN COMBAT!!!

    } break;
    case DUMMY:
        dummyInstance = new EnemyDummy(type, spawnPos);
        entities.add(dummyInstance);
        enemies.add(dummyInstance);
        break;
    case NPCDUMMY:
        dummyNpcInstance = new NpcDummy(type, spawnPos);
        entities.add(dummyNpcInstance);
        break;
    case EXIT:
        exitIntance = new Trigger(type, spawnPos);
        break;

    default :
        break;
    }
}

void ModuleEntities::RemoveEntity(PhysBody* entity)
{
    for (p2ListItem<Entity*>* aux = entities.getFirst(); aux != nullptr; aux = aux->next)
    {
        if (entity == aux->data->physBody)
        {
            aux->data->physBody->pendingToDelete = true;
            aux->data->Cleanup();

            delete aux->data;
            aux->data = nullptr;
        }
    }
}

void ModuleEntities::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

    //solve collsions here

    if (bodyA->type == PLAYEROPENWORLD || bodyB->type == PLAYEROPENWORLD)
    {
        switch (bodyB->type) 
        {
        case EXIT:
            app->levelManagement->gameScene = exitIntance->scene;
            break;
        case ENTRANCE:
            app->levelManagement->gameScene = entranceIntance->scene;
            break;
        default:
            break;
        }

    }



}


bool ModuleEntities::LoadState(pugi::xml_node& data)
{

    //clear all entities to load new ones
    for (p2ListItem<Entity*>* aux = entities.getFirst(); aux != nullptr; aux = aux->next)
    {
        aux->data->Cleanup();
        delete aux->data;
        aux->data = nullptr;
    }

    for (uint i = 0; i < MAX_ENTITIES; ++i)
    {
       
    }
    playerInstance = nullptr;
    pugi::xml_node currentEntitie = data.first_child();

    iPoint pos;

    while (currentEntitie != NULL )
    {
       Collider_Type type = static_cast<Collider_Type>(currentEntitie.attribute("type").as_int());
       float x = currentEntitie.attribute("x").as_int();
       float y = currentEntitie.attribute("y").as_int();
       pos = app->map->MapToWorld(x, y);
       AddEntity(type, pos);

       currentEntitie = currentEntitie.next_sibling();
    }

    for (p2ListItem<Entity*>* aux = entities.getFirst(); aux != nullptr; aux = aux->next)
    {
        aux->data->Start();
        aux->data->LoadState(data);

    }

    return true;
}

bool ModuleEntities::SaveState(pugi::xml_node& data) const
{
    for (p2ListItem<Entity*>* aux = entities.getFirst(); aux != nullptr; aux = aux->next)
    {
        aux->data->SaveState(data);
    }
    return true;
}

// Turns

bool ModuleEntities::CheckPlayerTurn() 
{
    for (p2ListItem<Player*>* aux = players.getFirst(); aux != nullptr; aux = aux->next)
    {
        if (aux->data->entityTurn == true)
           return true;
    }

    return false;
}

void ModuleEntities::NextEnemyTurn()
{
    for (p2ListItem<Enemy*>* aux = enemies.getFirst(); aux != nullptr; aux = aux->next)
    {
        if (aux->data->entityTurn == true)
        {
            aux->data->entityTurn = false;
          //  aux->next->data->entityTurn = true;
            enemiesAlive -= 1;
        }
    }
}

void ModuleEntities::StartPlayerTurn()
{
    for (p2ListItem<Player*>* aux = players.getFirst(); aux != nullptr; aux = aux->next)
    {
        aux->data->entityTurn = true;
    }

    app->levelManagement->combatState = PLAYERTURN;
}

void ModuleEntities::StartEnemiesTurn()
{
    enemies.getFirst()->data->entityTurn = true;
    enemiesAlive = enemies.count();
    app->levelManagement->combatState = ENEMYTURN;
}

PhysBody* ModuleEntities::GetNearestEnemy(PhysBody* Character)
{
    p2ListItem<Enemy*>* enemy = enemies.getFirst();
    if (enemy != NULL)
    {
        int temp = enemy->data->CheckDistanceToPhysBody(Character);

        PhysBody* nearEnemy = enemy->data->GetCollider();
        for (int i = 0; enemy; enemy = enemy->next)
        {


            int j = enemy->data->CheckDistanceToPhysBody(Character);
            if (j < temp)
            {
                temp = j;
                nearEnemy = enemy->data->GetCollider();
            }
        }
        return nearEnemy;
    }
    else return NULL;

}

PhysBody* ModuleEntities::GetNearestPlayer(PhysBody* Character)
{
    p2ListItem<Player*>* player = players.getFirst();
    if (player != NULL)
    {
        int temp = player->data->CheckDistanceToPhysBody(Character);

        PhysBody* nearEnemy = player->data->GetCollider();
        for (int i = 0; player; player = player->next)
        {


            int j = player->data->CheckDistanceToPhysBody(Character);
            if (j < temp)
            {
                temp = j;
                nearEnemy = player->data->GetCollider();
            }
        }
        return nearEnemy;
    }
    else return NULL;

}