#include "Entities.h"
#include "Point.h"
#include "Log.h"

#include "App.h"
#include "Audio.h"
#include "LevelManagement.h"

#include "Entity.h"

#include "Player.h"
#include "Knight.h"

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
        aux->data->Update(dt);
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
   
    return true;
}

void ModuleEntities::AddEntity(Collider_Type type, iPoint spawnPos)
{
    switch (type)
    {
    case PLAYER:
         playerInstance = new Player(type, spawnPos);
         entities.add(playerInstance);
        break;
    case PLAYERKNIGHT:
        knightInstance = new Knight(type, spawnPos);
        entities.add(knightInstance);
        break;
    case DUMMY:
        dummyInstance = new EnemyDummy(type, spawnPos);
        entities.add(dummyInstance);
        break;
    case NPCDUMMY:
        dummyNpcInstance = new NpcDummy(type, spawnPos);
        entities.add(dummyNpcInstance);
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

PhysBody* ModuleEntities::GetNearestEnemy(PhysBody* Character)
{
    p2ListItem<Enemy*>* enemy = enemies.getFirst();
    if (enemy != NULL)
    {
        int temp = enemy->data->CheckDistanceToPhysBody(Character);

        PhysBody* NearEnemy = enemy->data->GetCollider();
        for (int i = 0; enemy; enemy = enemy->next)
        {


            int j = enemy->data->CheckDistanceToPhysBody(Character);
            if (j < temp)
            {
                temp = j;
                NearEnemy = enemy->data->GetCollider();
            }
        }
        return NearEnemy;
    }
    else return NULL;

}