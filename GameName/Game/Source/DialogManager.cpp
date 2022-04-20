#include "DialogManager.h"


DialogManager::DialogManager()
{

}

DialogManager::~DialogManager()
{

}

bool DialogManager::LoadDialogs(const char* filename)
{
	bool ret = true;
	SString tmp("%s%s", folder.GetString(), filename);

	pugi::xml_document dialogFile;
	pugi::xml_parse_result result = dialogFile.load_file(tmp.GetString());

	if (result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", filename, result.description());
		ret = false;
	}

	if (ret == true)
	{
		// Create and call a private function to load and fill all your map data
		ret = LoadDialogGroups(dialogFile);
	}

	return ret;
}

bool DialogManager::LoadDialogGroups(pugi::xml_node dialogFile)
{
	
	
	for (pugi::xml_node group = dialogFile.child("dialog_group");
		group.next_sibling().name() == "dialog_group";
		group = group.next_sibling())
	{
		DialogGroup newDialogGroup;
		newDialogGroup.name = group.attribute("name").as_string();
		
		pugi::xml_node dialog;
		pugi::xml_node dialogIterator;
		

		for (dialog = group.child("dialog");
			dialog.next_sibling().name() == "dialog";
			dialog = dialog.next_sibling())
		{
			if (dialog.attribute("root").as_bool() == true)
			{
				//newDialogGroup.dialogNames.push_back(dialog.attribute("value").as_string());


				for (pugi::xml_node optionIterator = dialog.child("option");
					dialog.next_sibling().name() == "option";
					optionIterator = optionIterator.next_sibling())
				{
					LookForChildrenDialogues(group);
				}
				
				

			}


		}

		std::vector<Dialog*> dialogs;
		return true;
	}
		
		



	
}

pugi::xml_node DialogManager::LookForChildrenDialogues(pugi::xml_node group)
{
	pugi::xml_node ret;
	for (pugi::xml_node dialogIterator = group.child("dialog");
		dialogIterator.next_sibling().name() == "dialog";
		dialogIterator = dialogIterator.next_sibling())
	{


		if (dialogIterator.attribute("root").as_bool() == false)
		{

			for (pugi::xml_node optionIterator = dialogIterator.child("option");
				dialogIterator.next_sibling().name() == "option";
				optionIterator = optionIterator.next_sibling())
			{
				LookForChildrenDialogues(group);
			}

		}

	}



	return group;
}

bool DialogManager::AddDialog(Dialog dialog)
{
	return 1;
}