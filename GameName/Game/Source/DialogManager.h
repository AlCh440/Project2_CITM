/*#include "Dialog.h"
#include "Module.h"
#include "Log.h"
#include "SString.h"

struct DialogGroup
{
	std::string name;
	std::vector<std::string> dialogNames;
	std::vector<Dialog*> dialogs;
};


class DialogManager
{
public:

	DialogManager();
	~DialogManager();

	bool LoadDialogs(const char* filename);


private:
	SString folder;
	std::vector<DialogGroup> dialogGroups;
	

	/*int a()
	{
		DialogGroup group;
		group.name = "name";
		group.dialogNames.push_back("name");
		group.dialogs.push_back()
		
	}*/

	/*bool LoadDialogGroups(pugi::xml_node);
	pugi::xml_node LookForChildrenDialogues(pugi::xml_node children);

	bool AddDialog(Dialog dialog);

};*/


