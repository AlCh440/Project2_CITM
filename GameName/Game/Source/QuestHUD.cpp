#include "QuestHUD.h"
#include "App.h"
#include "QuestManager.h"

bool QuestHUD::Start()
{

    currentQuest = app->questManager->currentQuestList->start;
    return true;
}

bool QuestHUD::Update(float dt, bool doLogic)
{
    

    

    return true;
}

bool QuestHUD::Draw()
{

    

    return true;
}

bool QuestHUD::CleanUp()
{
    return true;
}
