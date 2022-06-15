#include "QuestManager.h"
#include "Log.h"
#include "Quest.h"

QuestManager::QuestManager(bool isActive) : Module(isActive)
{
	name.Create("quest_manager");
	toSave = true;
	saveConfigs = false;
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

bool QuestManager::Update(float dt)
{
	
		
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

		if (currentQuest->data->id == questID ) //&& currentQuest->data->progress == Quest::AVAILABLE
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

			switch (questID) // for rewards
			{
			case 1:

				break;

			}
		}

		currentQuest = currentQuest->next;
	}
}

//void QuestManager::FinishQuest(int questID)
//{
//	p2ListItem<Quest*>* currentQuest = questList->start;
//	while (currentQuest != NULL)
//	{
//
//		if (currentQuest->data->id == questID && currentQuest->data->progress == Quest::COMPLETE)
//		{
//			currentQuestList->add(currentQuest->data);
//			currentQuest->data->progress = Quest::DONE;
//		}
//
//		currentQuest = currentQuest->next;
//	}
//}

void QuestManager::AddItem()
{

}

bool QuestManager::GetAvailableQuest(int questID) const
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

bool QuestManager::GetActiveQuest(int questID) const
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

bool QuestManager::GetCompletedQuest(int questID) const
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
			quest->progress = Quest::AVAILABLE;
			quest->title = currentQuest.attribute("title").as_string();
			quest->description = currentQuest.child("description").child_value();
			quest->objective = currentQuest.child("objective").child_value();
			quest->coinsReward = currentQuest.child("rewards").child("coins").attribute("number").as_int();
			
			//generate text textures
			quest->titleTex = app->fonts->LoadRenderedText(quest->rTitle, app->fonts->titles,quest->title.GetString(), SDL_Color{ 32,27,46 });
			quest->descriptionTex = app->fonts->LoadRenderedParagraph(quest->rDescription, 0, quest->description.GetString(), SDL_Color{ 32,27,46 },500);
			quest->objectiveTex = app->fonts->LoadRenderedParagraph(quest->rObjective, 0, quest->objective.GetString(), SDL_Color{ 32,27,46 }, 500);

			questList->add(quest);

			currentQuest = currentQuest.next_sibling();
		}
	}

	return ret;
}

bool QuestManager::LoadState(pugi::xml_node& data)
{
	
	//gameScene = lm.attribute("first").as_int();

	//loadLevel = true;

	p2ListItem<Quest*>* currentQuest = questList->start;

	// 1 available
	// 2 active
	// 3 complete

	//while (currentQuest != NULL)
	//{
	//	switch (currentQuest->data->id)
	//	{
	//	case 0:
	//
	//		if (lm.attribute("first").as_int() == 1)
	//		{
	//			currentQuest->data->progress = Quest::AVAILABLE;
	//		}
	//		else if (lm.attribute("first").as_int() == 2)
	//		{
	//			currentQuest->data->progress = Quest::ACTIVE;
	//		}
	//		else if (lm.attribute("first").as_int() == 3)
	//		{
	//			currentQuest->data->progress = Quest::COMPLETE;
	//		}
	//		else
	//		{
	//			currentQuest->data->progress = Quest::AVAILABLE;
	//		}
	//
	//		break;
	//
	//	case 1:
	//
	//		if (lm.attribute("second").as_int() == 1)
	//		{
	//			currentQuest->data->progress = Quest::AVAILABLE;
	//		}
	//		else if (lm.attribute("second").as_int() == 2)
	//		{
	//			currentQuest->data->progress = Quest::ACTIVE;
	//		}
	//		else if (lm.attribute("second").as_int() == 3)
	//		{
	//			currentQuest->data->progress = Quest::COMPLETE;
	//		}
	//		else
	//		{
	//			currentQuest->data->progress = Quest::AVAILABLE;
	//		}
	//
	//		break;
	//
	//	case 2:
	//
	//		if (lm.attribute("third").as_int() == 1)
	//		{
	//			currentQuest->data->progress = Quest::AVAILABLE;
	//		}
	//		else if (lm.attribute("third").as_int() == 2)
	//		{
	//			currentQuest->data->progress = Quest::ACTIVE;
	//		}
	//		else if (lm.attribute("third").as_int() == 3)
	//		{
	//			currentQuest->data->progress = Quest::COMPLETE;
	//		}
	//		else
	//		{
	//			currentQuest->data->progress = Quest::AVAILABLE;
	//		}
	//
	//		break;
	//
	//	case 3:
	//
	//		if (lm.attribute("fourth").as_int() == 1)
	//		{
	//			currentQuest->data->progress = Quest::AVAILABLE;
	//		}
	//		else if (lm.attribute("fourth").as_int() == 2)
	//		{
	//			currentQuest->data->progress = Quest::ACTIVE;
	//		}
	//		else if (lm.attribute("fourth").as_int() == 3)
	//		{
	//			currentQuest->data->progress = Quest::COMPLETE;
	//		}
	//		else
	//		{
	//			currentQuest->data->progress = Quest::AVAILABLE;
	//		}
	//
	//		break;
	//
	//	case 4:
	//
	//		if (lm.attribute("fifth").as_int() == 1)
	//		{
	//			currentQuest->data->progress = Quest::AVAILABLE;
	//		}
	//		else if (lm.attribute("fifth").as_int() == 2)
	//		{
	//			currentQuest->data->progress = Quest::ACTIVE;
	//		}
	//		else if (lm.attribute("fifth").as_int() == 3)
	//		{
	//			currentQuest->data->progress = Quest::COMPLETE;
	//		}
	//		else
	//		{
	//			currentQuest->data->progress = Quest::AVAILABLE;
	//		}
	//
	//		break;
	//
	//	case 5:
	//
	//		if (lm.attribute("sixth").as_int() == 1)
	//		{
	//			currentQuest->data->progress = Quest::AVAILABLE;
	//		}
	//		else if (lm.attribute("sixth").as_int() == 2)
	//		{
	//			currentQuest->data->progress = Quest::ACTIVE;
	//		}
	//		else if (lm.attribute("sixth").as_int() == 3)
	//		{
	//			currentQuest->data->progress = Quest::COMPLETE;
	//		}
	//		else
	//		{
	//			currentQuest->data->progress = Quest::AVAILABLE;
	//		}
	//
	//		break;
	//
	//	default:
	//
	//		currentQuest->data->progress = Quest::AVAILABLE;
	//
	//		break;
	//	}
	//
	//	currentQuest = currentQuest->next;
	//}

	return true;
}

bool QuestManager::SaveState(pugi::xml_node& data) const
{
	
	pugi::xml_document* saveDoc = new pugi::xml_document();
	pugi::xml_node  saveStateNode = saveDoc->append_child("questList");


	pugi::xml_node node_01;
	pugi::xml_node node_02;
	pugi::xml_node node_03;
	for (p2ListItem<Quest*>* currentQuest = questList->start; currentQuest != nullptr; currentQuest = currentQuest->next)
	{
		node_01 = saveStateNode.append_child("quest");
		node_01.append_attribute("title").set_value(currentQuest->data->title.GetString());
		node_01.append_attribute("id") = currentQuest->data->id;
		if (currentQuest->data->progress == Quest::COMPLETE)
		{
			node_01.append_attribute("complete").set_name("true");
		}
		else
		{
			node_01.append_attribute("complete").set_name("false");
		}

		node_02 = node_01.append_child("description");
		node_02.append_attribute("text").set_value(currentQuest->data->description.GetString());

		node_02 = node_01.append_child("objective");
		node_02.append_attribute("text").set_value(currentQuest->data->objective.GetString());

		node_02 = node_01.append_child("rewards");
		node_03 = node_02.append_child("items");

	}
	
	saveDoc->save_file("quests.xml");
	p2ListItem<Quest*>* currentQuest = questList->start;
	
	// 1 available
	// 2 active
	// 3 complete

	//while (currentQuest != NULL)
	//{
	//	switch (currentQuest->data->id)
	//	{
	//	case 0:
	//
	//		if( GetAvailableQuest(currentQuest->data->id) ==true)
	//		{
	//			manager.append_attribute("first") = 1;
	//		}
	//		else if (GetActiveQuest(currentQuest->data->id) == true)
	//		{
	//			manager.append_attribute("first") = 2;
	//		}
	//		else if (GetCompletedQuest(currentQuest->data->id) == true)
	//		{
	//			manager.append_attribute("first") = 3;
	//		}
	//		else
	//		{
	//			manager.append_attribute("first") = -1;
	//		}
	//
	//		break;
	//	case 1:
	//
	//		if (GetAvailableQuest(currentQuest->data->id) == true)
	//		{
	//			manager.append_attribute("second") = 1;
	//		}
	//		else if (GetActiveQuest(currentQuest->data->id) == true)
	//		{
	//			manager.append_attribute("second") = 2;
	//		}
	//		else if (GetCompletedQuest(currentQuest->data->id) == true)
	//		{
	//			manager.append_attribute("second") = 3;
	//		}
	//		else
	//		{
	//			manager.append_attribute("second") = -1;
	//		}
	//
	//		break;
	//	case 2:
	//
	//		if (GetAvailableQuest(currentQuest->data->id) == true)
	//		{
	//			manager.append_attribute("third") = 1;
	//		}
	//		else if (GetActiveQuest(currentQuest->data->id) == true)
	//		{
	//			manager.append_attribute("third") = 2;
	//		}
	//		else if (GetCompletedQuest(currentQuest->data->id) == true)
	//		{
	//			manager.append_attribute("third") = 3;
	//		}
	//		else
	//		{
	//			manager.append_attribute("third") = -1;
	//		}
	//
	//		break;
	//	case 3:
	//
	//		if (GetAvailableQuest(currentQuest->data->id) == true)
	//		{
	//			manager.append_attribute("fourth") = 1;
	//		}
	//		else if (GetActiveQuest(currentQuest->data->id) == true)
	//		{
	//			manager.append_attribute("fourth") = 2;
	//		}
	//		else if (GetCompletedQuest(currentQuest->data->id) == true)
	//		{
	//			manager.append_attribute("fourth") = 3;
	//		}
	//		else
	//		{
	//			manager.append_attribute("fourth") = -1;
	//		}
	//
	//		break;
	//	case 4:
	//
	//		if (GetAvailableQuest(currentQuest->data->id) == true)
	//		{
	//			manager.append_attribute("fifth") = 1;
	//		}
	//		else if (GetActiveQuest(currentQuest->data->id) == true)
	//		{
	//			manager.append_attribute("fifth") = 2;
	//		}
	//		else if (GetCompletedQuest(currentQuest->data->id) == true)
	//		{
	//			manager.append_attribute("fifth") = 3;
	//		}
	//		else
	//		{
	//			manager.append_attribute("fifth") = -1;
	//		}
	//
	//		break;
	//	case 5:
	//
	//		if (GetAvailableQuest(currentQuest->data->id) == true)
	//		{
	//			manager.append_attribute("sixth") = 1;
	//		}
	//		else if (GetActiveQuest(currentQuest->data->id) == true)
	//		{
	//			manager.append_attribute("sixth") = 2;
	//		}
	//		else if (GetCompletedQuest(currentQuest->data->id) == true)
	//		{
	//			manager.append_attribute("sixth") = 3;
	//		}
	//		else
	//		{
	//			manager.append_attribute("sixth") = -1;
	//		}
	//
	//		break;
	//	default:
	//		manager.append_attribute("first") = -1;
	//		manager.append_attribute("second") = -1;
	//		manager.append_attribute("third") = -1;
	//		manager.append_attribute("fourth") = -1;
	//		manager.append_attribute("fifth") = -1;
	//		manager.append_attribute("sixth") = -1;
	//
	//		break;
	//	}
	//	
	//
	//	currentQuest = currentQuest->next;
	//}

	return true;
}

//bool LevelManagement::LoadState(pugi::xml_node& data)
//{
//
//	pugi::xml_node lm = data.child("levelManager");
//
//	gameScene = static_cast<GameScene>(lm.attribute("currentLevel").as_int());
//
//	loadLevel = true;
//	return true;
//}
//
//bool LevelManagement::SaveState(pugi::xml_node& data) const
//{
//	pugi::xml_node manager = data.append_child("levelManager");
//
//	manager.append_attribute("currentLevel") = gameScene;
//
//
//	return true;
//}