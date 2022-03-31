#include "QuestPanel.h"
#include "Log.h"
#include "App.h"
#include "GuiManager.h"
#include "QuestManager.h"

QuestPanel::QuestPanel(bool active) : GuiPanel(active)
{
	Active = active;
}

QuestPanel::~QuestPanel()
{
}

bool QuestPanel::Start()
{
	texture = app->guiManager->UItexture2;
	bounds = { 81,414,558,266 };
	position = { 81,414 };

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
	if (!Active)
		return false;

	if (doLogic) {

		p2ListItem<GuiControl*>* control = controls.start;

		while (control != nullptr)
		{
			control->data->Update(dt);
			control = control->next;
		}

	}
}

bool QuestPanel::Draw()
{
	if (!Active)
		return false;


	if(texture != NULL)
	 app->render->DrawTexture(texture, position.x, position.y, &bounds);

	p2ListItem<GuiControl*>* control = controls.start;

	while (control != nullptr)
	{
		control->data->Draw(app->render);
		control = control->next;
	}

	if (currentQuest != nullptr && currentQuest->data->titleTex != NULL)
		app->render->DrawTexture(currentQuest->data->titleTex, 300, 433, &currentQuest->data->rTitle);

	if (currentQuest != nullptr)
	{
		switch (currentQuest->data->progress)
		{
		case Quest::NOT_AVAILABLE:

			if (notAvailableTex != nullptr)
				app->render->DrawTexture(notAvailableTex, 134, 450, &notavailable);

			break;
		case Quest::AVAILABLE:

			if (availableTex != nullptr)
				app->render->DrawTexture(availableTex, 134, 450, &rAvailable);

			break;
		case Quest::ACTIVE:

			if (currentQuest != nullptr && currentQuest->data->descriptionTex != NULL)
				app->render->DrawTexture(currentQuest->data->descriptionTex, 134, 450, &currentQuest->data->rDescription);

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
		app->questManager->CanelQuest(currentQuest->data->id);
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
