/*#include "DialogNode.h"
#include "Log.h"

DialogManager::DialogManager(bool isActive) : Module(isActive)
{
	name.Create("dialog manager");
}

DialogManager::~DialogManager()
{
}

bool DialogManager::Awake(pugi::xml_node& config)
{

	LOG("Loading dialog file");
	bool ret = true;

	folder.Create(config.child("folder").child_value());

	LOG(folder.GetString());
	if (folder == NULL)
	{
		LOG("Could not load quest folder");
	}

	folder = "Assets/";
	//dialogFile = "dialog.xml";

	return ret;
}

bool DialogManager::Start()
{
	//Load the quest file, this can be for the hole game or
	// foreach level load quest file. 
	Load(questFile.GetString());

	return true;
}

bool DialogManager::CleanUp()
{
	dialogList->clear();
	currentDialogList->clear();
	return true;
}



void DialogManager::ActivateDialog(int questID)
{
	p2ListItem<DialogPanel*>* currentDialog = dialogList->start;
	while (currentDialog != NULL)
	{

		if (currentDialog->data->id == questID && currentDialog->data->progress == DialogPanel::AVAILABLE)
		{
			currentDialogList->add(currentDialog->data);
			currentDialog->data->progress = DialogPanel::ACTIVE;
		}

		currentDialog = currentDialog->next;
	}
}

void DialogManager::CanelQuest(int questID)
{
	p2ListItem<Quest*>* currentQuest = questList->start;
	while (currentQuest != NULL)
	{

		if (currentQuest->data->id == questID && currentQuest->data->progress == Quest::ACTIVE)
		{
			currentQuestList->add(currentQuest->data);
			currentQuest->data->progress = Quest::AVAILABLE;
		}

		currentQuest = currentQuest->next;
	}
}

void DialogManager::CompleteQuest(int questID)
{
	p2ListItem<Quest*>* currentQuest = questList->start;
	while (currentQuest != NULL)
	{

		if (currentQuest->data->id == questID && currentQuest->data->progress == Quest::ACTIVE)
		{
			currentQuestList->add(currentQuest->data);
			currentQuest->data->progress = Quest::COMPLETE;
		}

		currentQuest = currentQuest->next;
	}
}


void DialogManager::AddItem()
{
}

bool DialogManager::GetAvailableQuest(int questID)
{
	p2ListItem<Quest*>* currentQuest = questList->start;
	while (currentQuest != NULL)
	{

		if (currentQuest->data->id == questID && currentQuest->data->progress == Quest::AVAILABLE)
			return true;

		currentQuest = currentQuest->next;
	}
	return false;
}

bool DialogManager::GetActiveQuest(int questID)
{
	p2ListItem<Quest*>* currentQuest = questList->start;
	while (currentQuest != NULL)
	{

		if (currentQuest->data->id == questID && currentQuest->data->progress == Quest::ACTIVE)
			return true;

		currentQuest = currentQuest->next;
	}
	return false;
}

bool DialogManager::GetCompletedQuest(int questID)
{
	p2ListItem<Quest*>* currentQuest = questList->start;
	while (currentQuest != NULL)
	{

		if (currentQuest->data->id == questID && currentQuest->data->progress == Quest::COMPLETE)
			return true;

		currentQuest = currentQuest->next;
	}
	return false;
}

bool DialogManager::Load(const char* path)
{
	bool ret = true;
	SString tmp("%s%s", folder.GetString(), path);

	LOG("File path: %s", tmp.GetString());

	pugi::xml_document questsFile;
	pugi::xml_parse_result result = questsFile.load_file(tmp.GetString());
	pugi::xml_node currentQuest;

	if (result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", path, result.description());
		ret = false;
	}
	else {

		currentDialog = dialogsFile.child("dialog_list").first_child();

		while (currentDialog != NULL)
		{
			DialogPanel* dialog = new DialogPanel();

			//laod properties
			dialog->id = currentQuest.attribute("id").as_int();
			dialog->progress = Quest::NOT_AVAILABLE;
			dialog->title = currentQuest.attribute("title").as_string();
			dialog->description = currentQuest.child("description").child_value();

			//generate text textures
			dialog->titleTex = app->fonts->LoadRenderedText(quest->rTitle, app->fonts->titles, quest->title.GetString(), SDL_Color{ 32,27,46 });
			dialog->descriptionTex = app->fonts->LoadRenderedParagraph(quest->rDescription, 0, quest->description.GetString(), SDL_Color{ 32,27,46 }, 500);

			dialogList->add(quest);

			currentDialog = currentDialog.next_sibling();
		}
	}

	return ret;
}

bool DialogManager::LoadState(pugi::xml_node&)
{
	return false;
}

bool DialogManager::SaveState(pugi::xml_node&) const
{
	return false;
}*/