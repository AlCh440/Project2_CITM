/*#include "Module.h"
#include "p2List.h"
#include "Quest.h"
#include "Dialog.h"
#include "PugiXml/src/pugixml.hpp"
#include "App.h"
#include "Fonts.h"



class DialogManager : public Module {

public:
	DialogManager(bool isActive);
	~DialogManager();

	bool Awake(pugi::xml_node& config);
	bool Start();
	bool CleanUp();

public:

	p2List<DialogPanel*>* dialogList = new p2List<DialogPanel*>();
	p2List<DialogPanel*>* currentDialogList = new p2List<DialogPanel*>();

	//Activate Dialog
	void ActivateDialog(int questID);

	//Cancel Dialog
	void CancelDialog(int questID);

	//Complete Dialog
	void CompleteDialog(int questID);

	

	//Add item
	void AddItem();

	//Get available Dialog 
	bool GetAvailableDialog(int questID);

	//Get active Dialog
	bool GetActiveQuest(int questID);

	//Get complete Dialog
	bool GetCompletedDialog(int questID);

	//Load quest files 
	bool DialogManager::Load(const char* path);

	// Load / Save
	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&) const;


	SString folder;
	SString questFile;
};*/
