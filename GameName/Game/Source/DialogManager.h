#ifndef __DIALOG_MANAGER_H__
#define __DIALOG_MANAGER_H__

#include "App.h"
#include "Dialog.h"
#include "Module.h"
#include "Log.h"
#include "SString.h"
#include "Dialog.h"
#include "DialogNode.h"
#include "DialogFonts.h"
#include "OpenWorldPlayer.h"
#include "TheFall.h"
#include "Entities.h"
#include "TheVillage.h"

struct DialogGroup
{
	std::string name;
	std::vector<std::string> dialogNames;
	std::vector<Dialog*> dialogs;
};


class DialogManager : public Module
{
public:

	DialogManager(bool isActive);
	~DialogManager();

	bool Awake(pugi::xml_node&) override;
	bool Start() override;
	bool PreUpdate() override;
	bool Update(float dt) override;
	bool PostUpdate();
	// Called before quitting
	bool CleanUp();


	//bool LoadDialogs(const char* filename);


private:
	SString folder;
	std::vector<DialogGroup> dialogGroups;
	SDL_Texture* dialogImg;
	int font;

	//details
	SDL_Rect blackSquare;
	float blackSquareAlpha;

public:
	//Dialog test
	Dialog dialog_Test;
	void FillDialog_Test(Dialog& dialog);

	//Dialog intro
	Dialog dialog_intro;
	void FillDialog_Intro(Dialog& dialog);

	//Dialog NoName
	Dialog dialog_NoName;
	void FillDialog_NoName(Dialog& dialog);
	bool dialogActive_NoName = false;

	Dialog dialog_Guard;
	void FillDialog_Guard(Dialog& dialog);
	bool dialogActive_Guard = false;

	Dialog dialog_Villager;
	void FillDialog_Villager(Dialog& dialog);
	bool dialogActive_Villager = false;

	Dialog dialog_Ranger;
	void FillDialog_Ranger(Dialog& dialog);
	bool dialogActive_Ranger = false;

	Dialog dialog_RangerText;
	void FillDialog_RangerText(Dialog& dialog);
	bool dialogActive_RangerText = false;

	Dialog dialog_Wizard;
	void FillDialog_Wizard(Dialog& dialog);
	bool dialogActive_Wizard = false;

	Dialog dialog_General;
	void FillDialog_General(Dialog& dialog);
	bool dialogActive_General = false;

	Dialog dialog_ArchmageRoom;
	void FillDialog_ArchmageRoom(Dialog& dialog);
	bool dialogActive_ArchmageRoom = false;

	Dialog dialog_ArchmageCombat;
	void FillDialog_ArchmageCombat(Dialog& dialog);
	bool dialogActive_ArchmageCombat = false;
	


	/*int a()
	{
		DialogGroup group;
		group.name = "name";
		group.dialogNames.push_back("name");
		group.dialogs.push_back()
		
	}*/

	/*bool LoadDialogGroups(pugi::xml_node);
	pugi::xml_node LookForChildrenDialogues(pugi::xml_node children);

	bool AddDialog(Dialog dialog);*/

};


#endif