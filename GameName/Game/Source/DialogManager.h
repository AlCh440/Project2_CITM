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