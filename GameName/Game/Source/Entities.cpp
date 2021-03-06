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
#include "Goblin.h"
#include "KingGoblin.h"
#include "NpcGuard.h"
#include "NpcWoVillager.h"
#include "NpcArchmage.h"
#include "NpcArchmageComb.h"
#include "NpcGeneral.h"
#include "NpcRanger.h"
#include "NpcRangerVill.h"
#include "NpcWizard.h"
#include "Chest.h"

#include "DoorButton.h"
#include "Lever.h"

#include "LeverSystem.h"

ModuleEntities::ModuleEntities(bool isActive) : Module(isActive)
{
    name.Create("entities");
    toSave = true;
    saveConfigs = false;
    
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
   /* for (p2ListItem<Entity*>* aux = entities.getFirst(); aux != nullptr; aux = aux->next)
    {
        aux->data->Start();
    }*/

   
    return true;
}

bool ModuleEntities::PreUpdate()
{
    for (p2ListItem<Entity*>* aux = entities.getFirst(); aux != nullptr; aux = aux->next)
    {
        aux->data->DEBUG = DEBUG;
        aux->data->PreUpdate();
    }

    if (openWorld != nullptr && app->levelManagement->inCombat == false)
    {
        openWorld->DEBUG = DEBUG;
        openWorld->PreUpdate();
    }
    return true;
}

bool ModuleEntities::Update(float dt)
{
    for (p2ListItem<Entity*>* aux = entities.getFirst(); aux != nullptr; aux = aux->next)
    {

            aux->data->Update(dt);        
    }

    if (openWorld != nullptr && app->levelManagement->inCombat == false)
        openWorld->Update(dt);

    return true;
}

bool ModuleEntities::PostUpdate()
{
    for (p2ListItem<Entity*>* aux = entities.getFirst(); aux != nullptr; aux = aux->next)
    {
        aux->data->PostUpdate();
    }
  
    if (openWorld != nullptr && app->levelManagement->inCombat == false)
        openWorld->PostUpdate();
    return true;
}

bool ModuleEntities::CleanUp()
{
    p2ListItem <Entity*>* aux2 = nullptr;
    for (p2ListItem<Entity*>* aux1 = entities.getFirst(); aux1 != nullptr; aux1 = aux1->next)
    {
        aux1->data->Cleanup();
        if (aux2 != nullptr) entities.del(aux2);
        aux2 = aux1;
    }

    playerInstance = nullptr;
    knightInstance = nullptr;
    dummyInstance = nullptr;
    dummyNpcInstance = nullptr;
    goblinInstance = nullptr;
    kingGoblinInstance = nullptr;
    snakeInstance = nullptr;
    
    listButtonDoor.clear();
    listDoors.clear();

    listLever.clear();
    listLeverSystem.clear();


    players.clear();
    entities.clear();
    return true;
}

Entity* ModuleEntities::AddEntity(Collider_Type type, iPoint spawnPos)
{
    
    switch (type)
    {
    case PLAYER:

        break;
    case PLAYERKNIGHT:
        knightInstance = new Knight(type, spawnPos);
        entities.add(knightInstance);
        players.add(knightInstance);
        knightInstance->Start();
        knightPointer = knightInstance;
        break;
    case PLAYERRANGER:
        rangerInstance = new Ranger(type, spawnPos);
        entities.add(rangerInstance);
        players.add(rangerInstance);
        rangerInstance->Start();
        rangerPointer = rangerInstance;
        break;
    case PLAYEROPENWORLD:
    {
        if (openWorld == nullptr) 
        {
            openWorldInstance = new OpenWorldPlayer(type, spawnPos);
            openWorld = openWorldInstance;
            openWorld->Start();
        }
    } break;
    case DUMMY:
        dummyInstance = new EnemyDummy(type, spawnPos);
        entities.add(dummyInstance);
        enemies.add(dummyInstance);
        dummyInstance->Start();
        break;
    case SNAKE:
        snakeInstance = new EnemySnake(type, spawnPos);
        entities.add(snakeInstance);
        enemies.add(snakeInstance);
        snakeInstance->Start();
        break;
    case ARCHMAGE:
        archmageInstance = new EnemyArchmage(type, spawnPos);
        entities.add(archmageInstance);
        enemies.add(archmageInstance);
        archmageInstance->Start();
        break;
    
    case GOBLIN:
        goblinInstance = new Goblin(type, spawnPos);
        entities.add(goblinInstance);
        enemies.add(goblinInstance);
        goblinInstance->Start();
        break;
    case KINGGOBLIN:
        kingGoblinInstance = new KingGoblin(type, spawnPos);
        entities.add(kingGoblinInstance);
        enemies.add(kingGoblinInstance);
        kingGoblinInstance->Start();
        break;

    case NPCDUMMY:
        dummyNpcInstance = new NpcDummy(type, spawnPos);
        entities.add(dummyNpcInstance);
        dummyNpcInstance->Start();
        break;

    case NPCGUARD:
        dummyNpcGuardInstance = new NpcGuard(type, spawnPos);
        entities.add(dummyNpcGuardInstance);
        dummyNpcGuardInstance->Start();
        break;
    case NPCWOVILLAGER:
        dummyNpcWoVillagerInstance = new NpcWoVillager(type, spawnPos);
        entities.add(dummyNpcWoVillagerInstance);
        dummyNpcWoVillagerInstance->Start();
        break;
    case NPCRANGER:
        dummyNpcRangerInstance = new NpcRanger(type, spawnPos);
        entities.add(dummyNpcRangerInstance);
        dummyNpcRangerInstance->Start();
        break;
    case NPCRANGERVILL:
        dummyNpcRangerVillInstance = new NpcRangerVill(type, spawnPos);
        entities.add(dummyNpcRangerVillInstance);
        dummyNpcRangerVillInstance->Start();
        break;
    case NPCWIZARD:
        dummyNpcWizardInstance = new NpcWizard(type, spawnPos);
        entities.add(dummyNpcWizardInstance);
        dummyNpcWizardInstance->Start();
        break;
    case NPCGENERAL:
        dummyNpcGeneralInstance = new NpcGeneral(type, spawnPos);
        entities.add(dummyNpcGeneralInstance);
        dummyNpcGeneralInstance->Start();
        break;
    case NPCARCHMAGE:
        dummyNpcArchmageInstance = new NpcArchmage(type, spawnPos);
        entities.add(dummyNpcArchmageInstance);
        dummyNpcArchmageInstance->Start();
        break;
    case NPCARCHMAGECOMB:
        dummyNpcArchmageCombInstance = new NpcArchmageComb(type, spawnPos);
        entities.add(dummyNpcArchmageCombInstance);
        dummyNpcArchmageCombInstance->Start();
        break;

    case CHEST:
        itemInstance = new Chest(type, spawnPos);
        entities.add(itemInstance);
        itemInstance->Start();
        return itemInstance;
        break;
    case EXIT:
        exitIntance = new Trigger(type, spawnPos);
        exitIntance->Start();
        break;
    case DOOR_BUTTON:
    { 
        DoorButton* d = new DoorButton(type, spawnPos);
        d->Start();
        entities.add(d); 
    }
    default :
        break;
    }

    return nullptr;
}

void ModuleEntities::RemoveEntity(PhysBody* entity)
{
    for (p2ListItem<Entity*>* aux = entities.getFirst(); aux != nullptr; aux = aux->next)
    {
        if (entity == aux->data->physBody)
        {
            aux->data->physBody->pendingToDelete = true;
            aux->data->Cleanup();

            entities.del(aux);
            delete aux->data;
            aux->data = nullptr;
        }
    }
}

void ModuleEntities::RemoveAllEntities()
{
    for (p2ListItem<Entity*>* aux = entities.getFirst(); aux != nullptr; aux = aux->next)
    {
        aux->data->physBody->pendingToDelete = true;
        aux->data->Cleanup();

        entities.del(aux);
        delete aux->data;
        aux->data = nullptr;
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
        case GENERAL_ENTRANCE:
            app->levelManagement->gameScene = generalEntrance->scene;
            break;
        case MAGE_ENTRANCE:
            app->levelManagement->gameScene = mageEntrance->scene;
            break;
        case SHOP_ENTRANCE:
            app->levelManagement->gameScene = shopEntrance->scene;
            break;
        case COMBATTRIGGER:
            // change when there is multiple batle scenes
            Trigger* t = (Trigger*)bodyB->entityPtr;
            app->levelManagement->combatScene = t->scene;
            app->levelManagement->gameScene = COMBAT;
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
        if (openWorld == nullptr)
        {
            AddEntity(PLAYEROPENWORLD, iPoint(0, 0));
            openWorld->Start();
        }

        openWorld->LoadState(data);

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
   
    if (openWorld != nullptr)
        openWorld->SaveState(data);
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

void ModuleEntities::LinkDoors()
{
    //link button doors with doors
    p2ListItem<Door*>* doorItem;
    p2ListItem<DoorButton*>* doorButtonItem;

    doorButtonItem = listButtonDoor.start;
    doorItem = listDoors.start;

    while (doorButtonItem != nullptr)
    {
        while (doorItem != nullptr)
        {
            if (doorButtonItem->data->door == nullptr && doorButtonItem->data->id == doorItem->data->id)
            {

                doorButtonItem->data->door = doorItem->data;
                doorItem = listDoors.getFirst();
                break;
            }
            doorItem = doorItem->next;
        }
        doorButtonItem = doorButtonItem->next;
    }

    p2ListItem<Lever*>* leverItem = listLever.start;
    p2ListItem<LeverSystem*>* leverSystemItem = listLeverSystem.start;

     while (leverSystemItem != nullptr)
    {

        while (leverItem != nullptr)
        {

            if (leverItem->data->id == leverSystemItem->data->id)
            {
                leverSystemItem->data->levers.add(leverItem->data);
            }

            leverItem = leverItem->next;
        }
        //add the door
        while (doorItem != nullptr)
        {
            if (leverSystemItem->data->door == nullptr && leverSystemItem->data->id == doorItem->data->id)
            {

                leverSystemItem->data->door = doorItem->data;
                doorItem = listDoors.getFirst();
                break;
            }
            doorItem = doorItem->next;
        }
        leverSystemItem = leverSystemItem->next;
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

p2ListItem<Player*>* ModuleEntities::GetNearestPlayer(Entity* Character)
{
    p2ListItem<Player*>* ret = nullptr;
    p2ListItem<Player*>* player = players.getFirst();

    if (player != NULL)
    {
        int closest = Character->pathfinding->CreatePath(Character->tilePos,player->data->tilePos);
        ret = player;
        while(player != nullptr)
        {
            int temp = Character->pathfinding->CreatePath(Character->tilePos, player->data->tilePos);
            
            if (temp < closest)
            {
                closest = temp;
                ret = player;
            }

            player = player->next;
        }
        Character->pathfinding->ClearPath();
        return ret;

    }
    else return ret;

}