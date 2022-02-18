#include "ModuleEntities.h"
#include "Point.h"
#include "Log.h"

#include "App.h"
#include "Audio.h"
#include "LevelManagement.h"

#include "Entity.h"

#include "Player.h"
#include "Bat.h"
#include "Musher.h"
#include "BigMusher.h"
#include "Gem.h"
#include "Key.h"
#include "HPotion.h"
#include "CheckPoint.h"
#include "Portal.h"



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

    coinFx = app->audio->LoadFx("Assets/audio/fx/PickupCoin.wav");
    hitFx = app->audio->LoadFx("Assets/audio/fx/Hit.wav");

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
            case BAT:
                entities[i] = new Bat(type, spawnPos);
                break;
            case MUSHER:
                entities[i] = new Musher(type, spawnPos);
                break;
            case BIG_MUSHER:
                entities[i] = new BigMusher(type, spawnPos);
                break;
            case PLAYER:
                 entities[i] = playerInstance = new Player(type, spawnPos);
                break;
            case KEY:
                entities[i] = new Key(type,spawnPos);
                break;
            case GEM:
                entities[i] = new Gem(type,spawnPos);
                break;
            case POTION:
                entities[i] = new HPotion(type, spawnPos);
                break;
            case CHECK_POINT:
            {
                CheckPoint* p = new CheckPoint(type, spawnPos);
                entities[i] = p;
                checkPoint.add(p);
            }
                break;
            case PORTAL:
                entities[i] = portalInstance = new Portal(type, spawnPos);
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

    if (bodyA->type == Collider_Type::PLAYER)
    {
   
       switch (bodyB->type)
        {
        case Collider_Type::GEM:

            coinsCollected++;
            app->audio->PlayFx(coinFx);
            RemoveEntity(bodyB);
            break;
        case Collider_Type::KEY:
            app->levelManagement->KeysToTake--;
            playerInstance->keysCollected++;
            if (app->levelManagement->KeysToTake <= 0)
            {
                portalInstance->Transition();
            }
            RemoveEntity(bodyB);
            break;
        case Collider_Type::POTION:
            playerInstance->lives++;
            RemoveEntity(bodyB);
            break;
        case Collider_Type::DEATH:

            if (!playerInstance->isGodmodeOn)
                playerInstance->state = PlayerState::DEAD;
            break;
        case Collider_Type::MUSHER:
            if (!playerInstance->isGodmodeOn)
            {
                playerInstance->lives--;
                LOG("OUCH GOT HIT!");
                if (playerInstance->lives <= 0)
                {
                   playerInstance->state = PlayerState::DEAD;
                    LOG("KILL ME!");
                }
            }
            break;
        case Collider_Type::BIG_MUSHER:
            if (!playerInstance->isGodmodeOn)
            {
                playerInstance->lives--;
                LOG("OUCH GOT HIT!");
                if (playerInstance->lives <= 0)
                {
                    playerInstance->state = PlayerState::DEAD;
                    LOG("KILL ME!");
                }
            }
        case Collider_Type::BAT:
            if (!playerInstance->isGodmodeOn)
            {
                playerInstance->lives--;
                LOG("OUCH GOT HIT!");
                if (playerInstance->lives <= 0)
                {
                    playerInstance->state = PlayerState::DEAD;
                    LOG("KILL ME!");
                }
            }
            break;
        case Collider_Type::PORTAL:
            if (app->levelManagement->KeysToTake <= 0 && portalInstance->portalState == Portal::PortalState::P_OPEN)
            {
                app->levelManagement->gameState = app->levelManagement->GAME_OVER;
                LOG("I WON, GIVE ME TREAT!");
            }
            break;
        case Collider_Type::CHECK_POINT:
            {  
                p2List_item<CheckPoint*>* p = checkPoint.getFirst();
                while (p != NULL)
                {
                    if (p->data->physBody == bodyB)
                    {
                        p->data->Transition();
                        break;
                    }
                    p = p->next;
                }
                app->SaveGameRequest();

                LOG("CHECKPOINT! PROGRESS SAVED!");
            }
            break;
        default:
            break;
        }



    }else 
    if ((bodyA->type == Collider_Type::MUSHER || bodyA->type == Collider_Type::BAT || bodyA->type == Collider_Type::BIG_MUSHER) && bodyB->type == Collider_Type::PLAYER_ATTACK)
    {
        for (int i = 0; i < MAX_ENTITIES; i++)
        {
            if (entities[i] != nullptr)
            {
                if ((bodyA->type == Collider_Type::MUSHER || bodyA->type == Collider_Type::BAT) && entities[i]->physBody == bodyA)
                {
                    entities[i]->lives--;
                    if (entities[i]->lives <= 0)
                    {
                        app->audio->PlayFx(hitFx);
                        RemoveEntity(bodyA);
                        bodyA->pendingToDelete = true;
                    }
                }
                else if (bodyA->type == Collider_Type::BIG_MUSHER && entities[i]->physBody == bodyA)
                {
                    entities[i]->lives--;
                    if (entities[i]->lives <= 0)
                    {
                        app->audio->PlayFx(hitFx);
                        RemoveEntity(bodyA);
                        bodyA->pendingToDelete = true;
                    }
                }
            }
        }
    }

    playerInstance->wallLeft = false;
    playerInstance->wallRight = false;
    //For player movement
    if ((bodyA->type == PLAYER_X_SENSOR && bodyA->body != nullptr) &&bodyB->type == GROUND)
    {
        if (bodyA->body == playerInstance->leftSensor->body)
        {
            playerInstance->wallLeft = true;
        }
        if (bodyA->body == playerInstance->rightSensor->body)
        {
            playerInstance->wallRight = true;
        }
    }
    else if ((bodyA->type == PLAYER_Y_SENSOR && bodyA->body != nullptr) && bodyB->type == GROUND)
    {
        if (playerInstance->topSensor->body != NULL && bodyA->body == playerInstance->topSensor->body)
        {
        }
        else if (playerInstance->topSensor->body != NULL && bodyA->body == playerInstance->botSensor->body)
        {
            playerInstance->onGround = true;
            playerInstance->doubleJump = false;
            playerInstance->physBody->body->SetGravityScale(1);
        }
    }

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
