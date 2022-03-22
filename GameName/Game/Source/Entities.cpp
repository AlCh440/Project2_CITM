#include "Entities.h"
#include "Point.h"
#include "Log.h"

#include "App.h"
#include "Audio.h"
#include "LevelManagement.h"

#include "Entity.h"

#include "EnemyDummy.h"

#include "Player.h"
#include "CheckPoint.h"



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
    for (uint i = 0; i < MAX_ENTITIES; ++i)
    {

        if (entities[i] != nullptr)
        {
            entities[i]->Start();
        }
    }

   
    return true;
}

bool ModuleEntities::PreUpdate()
{
    for (uint i = 0; i < MAX_ENTITIES; ++i)
    {

        if (entities[i] != nullptr)
        {

             entities[i]->DEBUG = DEBUG;
             entities[i]->PreUpdate();
       
        }
    }

    return true;
}

bool ModuleEntities::Update(float dt)
{

    for (uint i = 0; i < MAX_ENTITIES; ++i)
    {
        if (entities[i] != nullptr)
            entities[i]->Update(dt);
    }

    return true;
}

bool ModuleEntities::PostUpdate()
{
    for (uint i = 0; i < MAX_ENTITIES; ++i)
    {
        if (entities[i] != nullptr)
            entities[i]->PostUpdate();
        
    }

    //this will be deleted
    a->PostUpdate();

    return true;

   
}

bool ModuleEntities::CleanUp()
{
    for (uint i = 0; i < MAX_ENTITIES; ++i)
    {
        if (entities[i] != nullptr)
        {
            entities[i]->Cleanup();
            delete entities[i];
            entities[i] = nullptr;
        }
    }
    return true;
}

void ModuleEntities::AddEntity(Collider_Type type, iPoint spawnPos)
{
    for (uint i = 0; i < MAX_ENTITIES; ++i)
    {
        if (entities[i] == nullptr)
        {
            switch (type)
            {
            case PLAYER:
                 entities[i] = playerInstance = new Player(type, spawnPos);
                break;

            default :
                break;
            }

            break;
        }
    }
}

void ModuleEntities::RemoveEntity(PhysBody* entity)
{
    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        if (entities[i]!= nullptr && entity == entities[i]->physBody)
        {
            entities[i]->physBody->pendingToDelete = true;
            entities[i]->Cleanup();
          
            delete entities[i];
            entities[i] = nullptr;

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
    for (uint i = 0; i < MAX_ENTITIES; ++i)
    {
        if (entities[i] != nullptr)
        {
            entities[i]->Cleanup();
            delete entities[i];
            entities[i] = nullptr;
        }
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

    for (uint i = 0; i < MAX_ENTITIES; ++i)
    {
        if (entities[i] != nullptr)
        {
            entities[i]->Start();
            entities[i]->LoadState(data);
        }
    }
    return true;
}

bool ModuleEntities::SaveState(pugi::xml_node& data) const
{
  
    for (uint i = 0; i < MAX_ENTITIES; ++i)
    {
        if (entities[i] != nullptr)
        {
            entities[i]->SaveState(data);
        }
    }
    return true;
}
