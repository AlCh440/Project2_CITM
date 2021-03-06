#include "Module.h"
#include "p2List.h"
#include "Quest.h"
#include "PugiXml/src/pugixml.hpp"
#include "App.h"
#include "Fonts.h"

#define QUEST_FILE "quests.xml"

class QuestManager : public Module {

public:
	QuestManager(bool isActive);
	~QuestManager();

	bool Awake(pugi::xml_node& config);
	bool Start();
	bool Update(float dt);
	bool CleanUp();

public: 

	p2List<Quest*>* questList = new p2List<Quest*>();
	p2List<Quest*>* currentQuestList = new p2List<Quest*>();

	//Activate Quest
	void ActivateQuest(int questID);

	//Cancel Quest
	void CancelQuest(int questID);

	//Complete Quest
	void CompleteQuest(int questID);

	//Finish Quest
	
	//Add item
	void AddItem();

	//Get available quest 
	bool GetAvailableQuest(int questID)const;

	//Get active quest
	bool GetActiveQuest(int questID)const;

	//Get complete quest but not Done (get rewards etc)
	bool GetCompletedQuest(int questID)const;

	//Load quest files 
	bool QuestManager::Load(const char* path);

	// Load / Save
	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&) const;


	SString folder;
	SString questFile;
};