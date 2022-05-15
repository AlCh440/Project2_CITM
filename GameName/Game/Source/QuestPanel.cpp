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

	texture = app->guiManager->UItexture2;
	bounds = { 81,414,558,266 };
	position = { 300,200 };

	notAvailableTex = app->fonts->LoadRenderedText(notavailable, 0, "Not available", {255,255,255});
	availableTex = app->fonts->LoadRenderedText(rAvailable,0, "There is something new!", { 255,255,255 });

	currentQuest = app->questManager->questList->start;

	nextButton = (GuiButton*)CreateGuiButton(0,app->guiManager,this, { 332, 610,52,56 });

	nextButton->texture = app->guiManager->UItexture2;
	nextButton->normalRec = { 0,297,56,52 };
	nextButton->focusedRec = { 0,349,56,52 };
	nextButton->pressedRec = { 0,349,56,52 };

	cancelButton = (GuiButton*)CreateGuiButton(1, app->guiManager, this, { 270, 610,52,56 });

	cancelButton->texture = app->guiManager->UItexture2;
	cancelButton->normalRec = {0,399,56,52};
	cancelButton->focusedRec = {0,451,56,52};
	cancelButton->pressedRec = {0,451,56,52};

	completeButton = (GuiButton*)CreateGuiButton(2, app->guiManager, this, { 210, 610,52,56 });

	completeButton->texture = app->guiManager->UItexture2;
	completeButton->normalRec = { 0,613,56,52 };
	completeButton->focusedRec = { 0,664,56,52 };
	completeButton->pressedRec = { 0,664,56,52 };

	dialogueButton = (GuiButton*)CreateGuiButton(3, app->guiManager, this, { 396, 610,52,56 });

	dialogueButton->texture = app->guiManager->UItexture2;
	dialogueButton->normalRec = { 57,349,56,52 };
	dialogueButton->focusedRec = { 57,297,56,52 };
	dialogueButton->pressedRec = { 57,297,56,52 };
	

    return true;
}

bool QuestPanel::Update(float dt, bool doLogic)
{
	GuiPanel::Update(dt,doLogic);
	//
	dialogueButton->position.x = 320 / app->win->GetScale();
	dialogueButton->position.y = 210 / app->win->GetScale();
	//
	return true;
}

bool QuestPanel::Draw()
{

	GuiPanel::Draw();

	if (currentQuest != nullptr && currentQuest->data->titleTex != NULL)
		app->render->DrawTexture(currentQuest->data->titleTex, 320 / app->win->GetScale(), 210 / app->win->GetScale(), &currentQuest->data->rTitle, 0, 0, 0, 0, 0.5f);
	
	if (currentQuest != nullptr && currentQuest->data->descriptionTex != NULL)
		app->render->DrawTexture(currentQuest->data->descriptionTex, 320 / app->win->GetScale(), 260 / app->win->GetScale(), &currentQuest->data->rDescription, 0, 0, 0, 0, 0.5f);

	if (currentQuest != nullptr && currentQuest->data->objectiveTex != NULL)
		app->render->DrawTexture(currentQuest->data->objectiveTex, 320 / app->win->GetScale(), 340 / app->win->GetScale(), &currentQuest->data->rObjective, 0, 0, 0, 0, 0.5f);

	if (currentQuest != nullptr)
	{
		switch (currentQuest->data->progress)
		{
		case Quest::NOT_AVAILABLE:

			if (notAvailableTex != nullptr)
				app->render->DrawTexture(notAvailableTex, 330 / app->win->GetScale(), 390 / app->win->GetScale(), &notavailable, 0, 0, 0, 0, 0.5f);

			break;
		case Quest::AVAILABLE:

			if (availableTex != nullptr)
				app->render->DrawTexture(availableTex, 330 / app->win->GetScale(), 390 / app->win->GetScale(), &rAvailable, 0, 0, 0, 0, 0.5f);

			break;
		case Quest::ACTIVE:

			if (currentQuest != nullptr && currentQuest->data->descriptionTex != NULL)
				app->render->DrawTexture(currentQuest->data->descriptionTex, 330 / app->win->GetScale(), 390 / app->win->GetScale(), &currentQuest->data->rDescription, 0, 0, 0, 0, 0.5f);

			break;
		case Quest::COMPLETE:

			break;
		case Quest::DONE:

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
	else if (control->id == cancelButton->id)
	{
		app->questManager->CancelQuest(currentQuest->data->id);
	}
	else if (control->id == completeButton->id)
	{
		app->questManager->CompleteQuest(currentQuest->data->id);
	}
	else if (control->id == dialogueButton->id)
	{
		app->questManager->ActivateQuest(currentQuest->data->id);
	}

	return true;
}
