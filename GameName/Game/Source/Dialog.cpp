#include "Dialog.h"
#include "Log.h"
#include "App.h"
#include "GuiManager.h"
#include "QuestManager.h"

DialogPanel::DialogPanel(bool active) : GuiPanel(active)
{
	Active = active;
}

DialogPanel::~DialogPanel()
{
}

bool DialogPanel::Start()
{
	//TODO add title

	texture = app->guiManager->UItexture2;
	bounds = { 81,414,558,266 };
	position = { 100,400 };

	notAvailableTex = app->fonts->LoadRenderedText(notavailable, 0, "Arnold The Guard", { 255,255,255 });
	availableTex = app->fonts->LoadRenderedText(rAvailable, 0, "There is something new!", { 255,255,255 });

	currentDialog = app->questManager->questList->start;



	cancelButton = (GuiButton*)CreateGuiButton(1, app->guiManager, this, { 270, 610,52,56 });

	cancelButton->texture = app->guiManager->UItexture2;
	cancelButton->normalRec = { 0,399,56,52 };
	cancelButton->focusedRec = { 0,451,56,52 };
	cancelButton->pressedRec = { 0,451,56,52 };


	dialogueButton = (GuiButton*)CreateGuiButton(3, app->guiManager, this, { 396, 610,52,56 });

	dialogueButton->texture = app->guiManager->UItexture2;
	dialogueButton->normalRec = { 57,349,56,52 };
	dialogueButton->focusedRec = { 57,297,56,52 };
	dialogueButton->pressedRec = { 57,297,56,52 };

	//DIALOGS
	answer1b = (GuiButton*)CreateGuiButton(3, app->guiManager, this, { 396, 610,52,56 });

	dialogueButton->texture = app->guiManager->UItexture2;
	dialogueButton->normalRec = { 57,349,56,52 };
	dialogueButton->focusedRec = { 57,297,56,52 };
	dialogueButton->pressedRec = { 57,297,56,52 };
	answer1Tex = app->fonts->LoadRenderedText(answer1, 0, "Who are you?", { 255,255,255 });

	return true;
}

bool DialogPanel::Update(float dt, bool doLogic)
{
	GuiPanel::Update(dt, doLogic);
	return true;
}

bool DialogPanel::Draw()
{

	GuiPanel::Draw();


	if (currentDialog != nullptr)
	{
		switch (currentDialog->data->progress)
		{
		case DialogPanel::NPC:

			if (notAvailableTex != nullptr)
				app->render->DrawTexture(notAvailableTex, 134, 450, &notavailable);

			break;
		case DialogPanel::PLAYER:

			if (availableTex != nullptr)
				app->render->DrawTexture(availableTex, 134, 450, &rAvailable);

			break;
		case DialogPanel::DONE:

			if (currentDialog != nullptr && currentDialog->data->descriptionTex != NULL)
				app->render->DrawTexture(currentDialog->data->descriptionTex, 134, 450, &currentDialog->data->rDescription);

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

bool DialogPanel::CleanUp()
{
	p2ListItem<GuiControl*>* control = controls.start;

	while (control != nullptr)
	{
		control->data->CleanUp();
		control = control->next;
	}
	return true;
}

bool DialogPanel::OnGuiMouseClickEvent(GuiControl* control)
{
	/*if (control->id == nextButton->id)
	{
		currentQuest = currentQuest->next;

		if (currentQuest == nullptr)
		{
			currentQuest = app->questManager->questList->start;
		}
	}*/
	if (control->id == cancelButton->id)
	{
		app->questManager->CanelQuest(currentDialog->data->id);
	}
	else if (control->id == dialogueButton->id)
	{
		app->render->DrawTexture(answer1Tex, 134, 450, &answer1);
		/*if (currentQuest != nullptr && currentQuest->data->titleTex != NULL)
			app->render->DrawTexture(currentQuest->data->titleTex, 300, 433, &currentQuest->data->rTitle);*/
		
		//app->questManager->ActivateQuest(currentQuest->data->id);
	}

	return true;
}