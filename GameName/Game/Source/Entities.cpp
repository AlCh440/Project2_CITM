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
#include "NpcGuard.h"
#include "NpcWoVillager.h"


ModuleEntities::ModuleEntities(bool isActive) : Module(isActive)
{
    name.Create("entities");
    toSave = true;
    
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
        //if (app->levelManagement->gameScene == 11)
        //{
        //    if (aux->data->entityTurn)
        //    {
        //        aux->data->Update(dt);
        //    }
        //}
        //else 
        //{
            aux->data->Update(dt);
        //}
        
    }
   
    //if (app->levelManagement->gameScene == 11)
    //{
    //    if (app->levelManagement->combatState == PLAYERTURN)
    //    {
    //        if (!CheckPlayerTurn())
    //        {
    //            StartEnemiesTurn();
    //        }
    //    }
    //    else if (app->levelManagement->combatState == ENEMYTURN)
    //    {
    //        if (enemiesAlive <= 0)
    //        {
    //            StartPlayerTurn();
    //        }
    //    }
    //}
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
    listOfCombatTriggers.clear();
    return true;
}

void ModuleEntities::AddEntity(Collider_Type type, iPoint spawnPos)
{
    switch (type)
    {
    case PLAYER:

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
    case NPCGUARD:
        dummyNpcGuardInstance = new NpcGuard(type, spawnPos);
        entities.add(dummyNpcGuardInstance);
        break;
    case NPCWOVILLAGER:
        dummyNpcWoVillagerInstance = new NpcWoVillager(type, spawnPos);
        entities.add(dummyNpcWoVillagerInstance);
        break;
    case EXIT:
        exitIntance = new Trigger(type, spawnPos);
        break;
    case GENERAL_ENTRANCE:
        generalEntrance = new Trigger(type, spawnPos);
        break;
    case MAGE_ENTRANCE:
        mageEntrance = new Trigger(type, spawnPos);
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
        case COMBATTRIGGER:
            app->levelManagement->gameScene = COMBAT; // change when there is multiple batle scenes
            break;
        default:
            break;
        }

    }
}


bool ModuleEntities::LoadState(pugi::xml_node& data)
{

    if (app->levelManagement->gameScene == COMBAT || app->levelManagement->gameScene == GAME_OVER ||
        app->levelManagement->gameScene == INTRO || app->levelManagement->gameScene == START)
    {

    }
    else
    {
        for (p2ListItem<Entity*>* aux = entities.getFirst(); aux != nullptr; aux = aux->next)
        {
            aux->data->LoadState(data);
        }
    }
    return true;
}

bool ModuleEntities::SaveState(pugi::xml_node& data) const
{
    if (app->levelManagement->gameScene == COMBAT || app->levelManagement->gameScene == GAME_OVER ||
        app->levelManagement->gameScene == INTRO || app->levelManagement->gameScene == START)
    {

    }
    else
    {
        for (p2ListItem<Entity*>* aux = entities.getFirst(); aux != nullptr; aux = aux->next)
        {
            aux->data->SaveState(data);
        }
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

           
            if (aux->next != nullptr)
            {
                aux->data->entityTurn = false;
                aux->next->data->entityTurn = true;
                enemiesAlive -= 1;
            }
            else
            {
                StartPlayerTurn();
            }
           

        }
    }
}

Entity* ModuleEntities::GetEntityFromTile(iPoint pos)
{
    p2ListItem<Entity*>* ent = entities.start;

    while (ent != nullptr)
    {
        if (ent->data->tilePos == pos)
            return ent->data;
        ent = ent->next;
    }
    return nullptr;
}

void ModuleEntities::StartPlayerTurn()
{
    for (p2ListItem<Player*>* aux = players.getFirst(); aux != nullptr; aux = aux->next)
    {
        aux->data->entityTurn = true;
    }

    //app->levelManagement->combatState = PLAYERTURN;
}

void ModuleEntities::StartEnemiesTurn()
{
    //enemies.getFirst()->data->entityTurn = true;
    //enemiesAlive = enemies.count();
    //app->levelManagement->combatState = ENEMYTURN;
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