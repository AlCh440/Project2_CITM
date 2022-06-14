#include "QuestPanel.h"
#include "Log.h"
#include "App.h"
#include "GuiManager.h"
#include "QuestManager.h"
#include "Window.h"

QuestPanel::QuestPanel(bool active) : GuiPanel(active)
{
	Active = active;
	id = PanelID::P_QUEST;

}

QuestPanel::~QuestPanel()
{
}

bool QuestPanel::Start()
{
	//TODO add title
	windowScale = app->win->GetScale();
	texture = app->guiManager->UItexture2;
	bounds = { 81,414,558,266 };
	position = { 300,200 };

	notAvailableTex = app->fonts->LoadRenderedText(notavailable, 0, "Locked", {255,255,255});
	availableTex = app->fonts->LoadRenderedText(rAvailable,0, "Unlocked", { 255,255,255 });
	activeTex = app->fonts->LoadRenderedText(rActive, 0, "Active", { 255,255,255 });
	completedTex = app->fonts->LoadRenderedText(rCompleted, 0, "Completed", { 255,255,255 });

	currentQuest = app->questManager->questList->start;


	nextButton = (GuiButton*)CreateGuiButton(0,app->guiManager,this, { 0 / windowScale, 535 / windowScale,52,56 });
	
	nextButton->texture = app->guiManager->UItexture2;
	nextButton->normalRec = { 0,297,56,52 };
	nextButton->focusedRec = { 0,349,56,52 };
	nextButton->pressedRec = { 0,349,56,52 };

	//completeButton = (GuiButton*)CreateGuiButton(1, app->guiManager, this, { 200 / windowScale, 535 / windowScale,52,56 });
	//
	//completeButton->texture = app->guiManager->UItexture2;
	//completeButton->normalRec = { 0,613,56,52 };
	//completeButton->focusedRec = { 0,664,56,52 };
	//completeButton->pressedRec = { 0,664,56,52 };
	
	offQuestPanel = (GuiButton*)CreateGuiButton(2, app->guiManager, this, { 1000 / windowScale, 535 / windowScale,52,56 });
	
	offQuestPanel->texture = app->guiManager->UItexture2;
	offQuestPanel->normalRec = {0,399,56,52};
	offQuestPanel->focusedRec = {0,451,56,52};
	offQuestPanel->pressedRec = {0,451,56,52};
	
	

	
	

    return true;
}

bool QuestPanel::Update(float dt, bool doLogic)
{
	
 	app->gamePaused = true;

	GuiPanel::Update(dt,doLogic);
	return true;
}

bool QuestPanel::Draw()
{
	app->gamePaused = true;
	//app->guiManager->OnPause(true);

	GuiPanel::Draw();

	if (currentQuest != nullptr && currentQuest->data->titleTex != NULL)
		app->render->DrawTexture(currentQuest->data->titleTex, 320 / app->win->GetScale(), 210 / app->win->GetScale(), &currentQuest->data->rTitle, 0, 0, 0, 0, 0.5f);
	
	
	//if (currentQuest != nullptr && currentQuest->data->descriptionTex != NULL)
	//	app->render->DrawTexture(currentQuest->data->descriptionTex, 320 / app->win->GetScale(), 260 / app->win->GetScale(), &currentQuest->data->rDescription, 0, 0, 0, 0, 0.5f);
	//
	//if (currentQuest != nullptr && currentQuest->data->objectiveTex != NULL)
	//	app->render->DrawTexture(currentQuest->data->objectiveTex, 320 / app->win->GetScale(), 340 / app->win->GetScale(), &currentQuest->data->rObjective, 0, 0, 0, 0, 0.5f);

	if (currentQuest != nullptr)
	{
		switch (currentQuest->data->progress)
		{
		//case Quest::NOT_AVAILABLE:
		//
		//	if (notAvailableTex != nullptr)
		//		app->render->DrawTexture(notAvailableTex, 330 / app->win->GetScale(), 390 / app->win->GetScale(), &notavailable, 0, 0, 0, 0, 0.5f);
		//
		//	break;
		case Quest::AVAILABLE:

			if (availableTex != nullptr)
				app->render->DrawTexture(notAvailableTex, 330 / app->win->GetScale(), 390 / app->win->GetScale(), &notavailable, 0, 0, 0, 0, 0.5f);

			break;
		case Quest::ACTIVE:

			//if (currentQuest != nullptr && currentQuest->data->descriptionTex != NULL)
			//	app->render->DrawTexture(currentQuest->data->descriptionTex, 330 / app->win->GetScale(), 390 / app->win->GetScale(), &currentQuest->data->rDescription, 0, 0, 0, 0, 0.5f);

			if (currentQuest != nullptr && currentQuest->data->descriptionTex != NULL)
				app->render->DrawTexture(currentQuest->data->descriptionTex, 320 / app->win->GetScale(), 260 / app->win->GetScale(), &currentQuest->data->rDescription, 0, 0, 0, 0, 0.5f);

			if (currentQuest != nullptr && currentQuest->data->objectiveTex != NULL)
				app->render->DrawTexture(currentQuest->data->objectiveTex, 320 / app->win->GetScale(), 340 / app->win->GetScale(), &currentQuest->data->rObjective, 0, 0, 0, 0, 0.5f);

			if (availableTex != nullptr)
				app->render->DrawTexture(activeTex, 330 / app->win->GetScale(), 390 / app->win->GetScale(), &rActive, 0, 0, 0, 0, 0.5f);

			break;
		case Quest::COMPLETE:

			if (currentQuest != nullptr && currentQuest->data->descriptionTex != NULL)
				app->render->DrawTexture(currentQuest->data->descriptionTex, 320 / app->win->GetScale(), 260 / app->win->GetScale(), &currentQuest->data->rDescription, 0, 0, 0, 0, 0.5f);

			if (currentQuest != nullptr && currentQuest->data->objectiveTex != NULL)
				app->render->DrawTexture(currentQuest->data->objectiveTex, 320 / app->win->GetScale(), 340 / app->win->GetScale(), &currentQuest->data->rObjective, 0, 0, 0, 0, 0.5f);

			if (availableTex != nullptr)
				app->render->DrawTexture(completedTex, 330 / app->win->GetScale(), 390 / app->win->GetScale(), &rCompleted, 0, 0, 0, 0, 0.5f);

			break;
		
		default:
			break;
		}

	}
	else {
		LOG("Quest is NULL");
	}

	
	

	return true;
}

bool QuestPanel::CleanUp()
{
	p2ListItem<GuiControl*>* control = controls.start;

	while (control != nullptr)
	{
		control->data->CleanUp();
		control = control->next;
	}
	return true;
}

bool QuestPanel::OnGuiMouseClickEvent(GuiControl* control)
{
	if (control->id == nextButton->id)
	{
		currentQuest = currentQuest->next;

		if (currentQuest == nullptr)
		{
			currentQuest = app->questManager->questList->start;
		}
	}
	//else if (control->id == completeButton->id)
	//{
	//	app->questManager->CompleteQuest(currentQuest->data->id);
	//	//app->questManager->CancelQuest(currentQuest->data->id);
	//}
	else if (control->id == offQuestPanel->id)
	{
		app->gamePaused = false;
		app->guiManager->OnPause(false);
		//app->questManager->CompleteQuest(currentQuest->data->id);
		//app->questManager->CancelQuest(currentQuest->data->id);
		this->Disable();
	}
	
	

	return true;
}
