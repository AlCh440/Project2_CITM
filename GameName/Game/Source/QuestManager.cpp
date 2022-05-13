#include "QuestManager.h"
#include "Log.h"

QuestManager::QuestManager(bool isActive) : Module(isActive)
{
	name.Create("quest_manager");
	toSave = false;
}

QuestManager::~QuestManager()
{
}

bool QuestManager::Awake(pugi::xml_node& config)
{

	LOG("Loading quests file");
	bool ret = true;

	folder.Create(config.child("folder").child_value());

	LOG(folder.GetString());
	if (folder == NULL)
	{
		LOG("Could not load quest folder");
	}

	folder = "Assets/";
	questFile = "quests.xml";

	return ret;
}

bool QuestManager::Start()
{
	//Load the quest file, this can be for the hole game or
	// foreach level load quest file. 
	Load(questFile.GetString());
	
	return true;
}

bool QuestManager::CleanUp()
{
	questList->clear();
	currentQuestList->clear();
	return true;
}



void QuestManager::ActivateQuest(int questID)
{
	p2ListItem<Quest*>* currentQuest = questList->start;
	while (currentQuest != NULL)
	{

		if (currentQuest->data->id == questID && currentQuest->data->progress == Quest::AVAILABLE)
		{
			currentQuestList->add(currentQuest->data);
			currentQuest->data->progress = Quest::ACTIVE;
		}

		currentQuest = currentQuest->next;
	}
}

void QuestManager::CancelQuest(int questID)
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

void QuestManager::CompleteQuest(int questID)
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

void QuestManager::FinishQuest(int questID)
{
	p2ListItem<Quest*>* currentQuest = questList->start;
	while (currentQuest != NULL)
	{

		if (currentQuest->data->id == questID && currentQuest->data->progress == Quest::COMPLETE)
		{
			currentQuestList->add(currentQuest->data);
			currentQuest->data->progress = Quest::DONE;
		}

		currentQuest = currentQuest->next;
	}
}

void QuestManager::AddItem()
{
}

bool QuestManager::GetAvailableQuest(int questID)
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

bool QuestManager::GetActiveQuest(int questID)
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

bool QuestManager::GetCompletedQuest(int questID)
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

bool QuestManager::Load(const char* path) 
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

		currentQuest = questsFile.child("quests_list").first_child();

		while (currentQuest != NULL)
		{
			Quest* quest = new Quest();

			//laod properties
			quest->id = currentQuest.attribute("id").as_int();
			quest->progress = Quest::NOT_AVAILABLE;
			quest->title = currentQuest.attribute("title").as_string();
			quest->description = currentQuest.child("description").child_value();
			
			//generate text textures
			quest->titleTex = app->fonts->LoadRenderedText(quest->rTitle, app->fonts->titles,quest->title.GetString(), SDL_Color{ 32,27,46 });
			quest->descriptionTex = app->fonts->LoadRenderedParagraph(quest->rDescription, 0, quest->description.GetString(), SDL_Color{ 32,27,46 },500);

			questList->add(quest);

			currentQuest = currentQuest.next_sibling();
		}
	}

	return ret;
}

bool QuestManager::LoadState(pugi::xml_node&)
{
	return true;
}

bool QuestManager::SaveState(pugi::xml_node&) const
{
	return true;
}
