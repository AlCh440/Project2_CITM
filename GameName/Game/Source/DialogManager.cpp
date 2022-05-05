#include "DialogManager.h"


DialogManager::DialogManager(bool isActive) : Module(isActive)
{
	name.Create("gui manager");
}

DialogManager::~DialogManager()
{

}

bool DialogManager::Awake(pugi::xml_node&)
{
	return true;
}

bool DialogManager::Start()
{
	 dialogImg = app->tex->Load("Assets/Sprites/UI/dialog_box_paper.png");

	 char lookupTable[] = { "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[£]çç€!ççç%&'()*+,-.^0123456789:;<=>?/abcdefghijklmnopqrstuvwxyz ççççççç" };
	 char lookupTable2[] = { " !ç#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[ç]^_çabcdefghijklmnopqrstuvwxyz{|}~" };

	 font = app->dialogFonts->Load("Assets/Sprites/UI/Fonts/NeoSans.png", lookupTable2, 1);

	//fill dialogs

	//test dialog
	FillDialog_Intro(dialog_intro);
	FillDialog_Test(dialog_Test);
	FillDialog_NoName(dialog_NoName);
	FillDialog_Guard(dialog_Guard);
	FillDialog_Villager(dialog_Villager);

	float screenScale = 1 / (float)app->win->GetScale();

	//details;
	blackSquare = { 0,0,app->win->GetWidth(), app->win->GetHeight()};
	blackSquareAlpha = 255;
	return true;
}

bool DialogManager::PreUpdate()
{

	return true;
}

bool DialogManager::Update(float dt)
{
	return true;
}

bool DialogManager::PostUpdate()
{

	OpenWorldPlayer* player = (OpenWorldPlayer*)app->entities->playerInstance;

	
	
	if (app->theFall->active)
	{
		
		app->render->DrawRectangle(blackSquare, 0, 0, 0, blackSquareAlpha, true, false);
		if ((!dialog_intro.Finished()))
		{
			

			if (player != nullptr) player->SetMotion(false);
			dialog_intro.Update();
		}
		else
		{
			if (player != nullptr) player->SetMotion(true);
			if (blackSquareAlpha - 2 > 0) 
				blackSquareAlpha -= 2;
			else {
				blackSquareAlpha = 0;
			}
		}


		if (dialogActive_NoName)
		{
			if ((!dialog_NoName.Finished()))
			{
				if (player != nullptr) player->SetMotion(false);
				dialog_NoName.Update();
			}
			else
			{
				if (player != nullptr) player->SetMotion(true);
				dialogActive_NoName = false;
			}
		}

		
		}
	
	if (app->village->active)
	{
		if (app->dialogManager->dialogActive_Guard)
		{
			if ((!dialog_Guard.Finished()))
			{
				if (player != nullptr) player->SetMotion(false);
				dialog_Guard.Update();
			}
			else
			{
				if (player != nullptr) player->SetMotion(true);
				dialogActive_Guard = false;
			}
		}

		if (app->dialogManager->dialogActive_Villager)
		{
			if ((!dialog_Villager.Finished()))
			{
				if (player != nullptr) player->SetMotion(false);
				dialog_Villager.Update();
			}
			else
			{
				if (player != nullptr) player->SetMotion(true);
				dialogActive_Villager = false;
			}
		}
	}
	

	return true;
}

bool DialogManager::CleanUp()
{

	return true;
}

void DialogManager::FillDialog_Intro(Dialog& dialog)
{
	// Take dialog box, and font

	// Set dialog box, and font
	dialog.SetPosition(340, 260);
	dialog.SetDialogBg(dialogImg, 600, 206, 20, 20);
	dialog.SetFont(font);

	// Fill the dialog
	DialogNode node;

	// Last branch
	size_t id;


	node.text = "I wish you luck on your journey.";
	id = dialog.AddNode(node);

	node.text = "Anyways...";
	node.nodes.push_back(id);
	id = dialog.AddNode(node);

	node.text = "And you, my dear player, are that opponent. It's a shame that you don't remember any of this...";
	node.nodes.push_back(id);
	id = dialog.AddNode(node);

	node.text = "The powerful archel who sent this world to its demise only to find a worthy opponent.";
	node.nodes.push_back(id);
	id = dialog.AddNode(node);

	node.text = "I am Anmague.";
	node.nodes.push_back(id);
	id = dialog.AddNode(node);

	node.text = "Let's leave these generic introductions aside and get to the point.";
	node.nodes.push_back(id);
	id = dialog.AddNode(node);

	node.text = "You know what?";
	node.nodes.push_back(id);
	id = dialog.AddNode(node);

	node.text = "Ugh...";
	node.nodes.push_back(id);
	id = dialog.AddNode(node);

	node.text = "Once upon a time, in a world desolated by chaotic energies, caused by a  powerful arc...";
	node.nodes.push_back(id);
	id = dialog.AddNode(node);

	dialog.SetActiveNode(id);
}

void DialogManager::FillDialog_NoName(Dialog& dialog)
{

	// Set dialog box, and font
	dialog.SetPosition(340, 260);
	dialog.SetDialogBg(dialogImg, 600, 206, 20, 20);
	dialog.SetFont(font);

	// Fill the dialog
	DialogNode node;

	size_t id;

	//// Last branch
	//size_t id;
	//node.text = "bla bla bla bla bla bla bla bla bla bla bla bla bla bla bla bla bla...";

	//id = dialog.AddNode(node);

	//node.text = "alright... let me tell you who i am.";
	//node.nodes.push_back(id);

	//id = dialog.AddNode(node);

	//// Branch 1
	//size_t id_1;

	//node.text = "are you sure you never heard of ralph the mage master?";
	//node.nodes.push_back(id);

	//id_1 = dialog.AddNode(node);

	//node.text = "...";
	//node.nodes.push_back(id_1);

	//id_1 = dialog.AddNode(node);

	//// Branch 2
	//size_t id_2;

	//node.text = "of course, i am famous!";
	//node.nodes.push_back(id);
	//node.options.push_back("just kidding, never heard of you.");

	//id_2 = dialog.AddNode(node);

	//// Branch 3
	//size_t id_3;

	//node.text = "i would never trick you, i am good, i help people!";
	//node.nodes.push_back(id);

	//id_3 = dialog.AddNode(node);

	//node.text = "what? why would i do that?!";
	//node.nodes.push_back(id_3);

	//id_3 = dialog.AddNode(node);

	//// Connect to main branch
	//node.text = "i am sure you heard speak of me!";
	//node.nodes.push_back(id_1);
	//node.options.push_back("uh... no?");

	//node.nodes.push_back(id_2);
	//node.options.push_back("oh yes I remember");

	//node.nodes.push_back(id_3);
	//node.options.push_back("are you trying to trick me?");

	//id = dialog.AddNode(node);

	//node.text = "i am ralph, the mage master!";
	//node.nodes.push_back(id);

	//id = dialog.AddNode(node);

	//node.text = "text branch 1";
	//node.nodes.push_back(id);
	//node.options.push_back("Option 1");

	//node.nodes.push_back(id);
	//node.options.push_back("Option 2");

	//id = dialog.AddNode(node);

	//dialog.SetActiveNode(id);

	////////////////////////////////////////////////////////////////////////////

	/*
	
	
	
	*/
	size_t id_2_;


	node.text = "You leave the conversation in the air.";
	id = dialog.AddNode(node);

	node.text = "(quietely)  The things I do for the team...";

	id_2_ = dialog.AddNode(node);

	node.text = "Great, on you go!";
	node.nodes.push_back(id_2_);
	id_2_ = dialog.AddNode(node);

	node.text = "Kill them, if you want to accept the quest, of course";

	node.nodes.push_back(id_2_);
	node.options.push_back("I accept it.");

	node.nodes.push_back(id);
	node.options.push_back("I don't accept the quest.");

	id_2_ = dialog.AddNode(node);




	node.text = "You see those snakes with swords there?";
	node.nodes.push_back(id_2_);
	id_2_ = dialog.AddNode(node);

	node.text = "A questy quest?";
	node.nodes.push_back(id_2_);
	id_2_ = dialog.AddNode(node);

	node.text = "A really worthy quest!";
	node.nodes.push_back(id_2_);
	id_2_ = dialog.AddNode(node);

	size_t id_3_;


	

	node.text = "You leave the conversation in the air.";
	id = dialog.AddNode(node);

	node.text = "Great! Anyways, a quest for you, blue boy.";
	node.nodes.push_back(id_2_);
	id_3_ = dialog.AddNode(node);

	node.text = "Great! Anyways, a quest for you, red boy.";
	node.nodes.push_back(id_2_);
	id_2_ = dialog.AddNode(node);

	size_t id_1_;

	node.text = "Do you like Red or Blue?";

	node.nodes.push_back(id_2_);
	node.options.push_back("Red.");

	node.nodes.push_back(id_3_);
	node.options.push_back("Blue.");

	node.nodes.push_back(id);
	node.options.push_back("Leave.");

	id_1_ = dialog.AddNode(node);

	node.text = "Questions!";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "...Uhm...";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "Anyways, here i am, i talk, and you respond, i am a completely vehicle NPC, with natural dialogs and...";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "Can you believe it?";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "We could add a sign that lets you know that we have a dialogue system, but it wouldn't count as a NPC just because it has a different tile!";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "Of course i do, i must, else the Matucana Team won’t get the NPC point!";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "Not even a chance to start a conversation.";
	id = dialog.AddNode(node);

	id = dialog.AddNode(node);

	node.text = "...";
	node.nodes.push_back(id_1_);
	node.options.push_back("Do you talk?");

	node.nodes.push_back(id);
	node.options.push_back("Leave.");

	id = dialog.AddNode(node);

	dialog.SetActiveNode(id);




}

void DialogManager::FillDialog_Test(Dialog& dialog)
{

	// Set dialog box, and font
	dialog.SetPosition(340, 260);
	dialog.SetDialogBg(dialogImg, 600, 206, 20, 20);
	dialog.SetFont(font);

	// Fill the dialog
	DialogNode node;

	// Last branch
	size_t id;
	node.text = "bla bla bla bla bla bla bla bla bla bla bla bla bla bla bla bla bla...";

	id = dialog.AddNode(node);

	node.text = "alright... let me tell you who i am.";
	node.nodes.push_back(id);

	id = dialog.AddNode(node);

	// Branch 1
	size_t id_1;

	node.text = "are you sure you never heard of ralph the mage master?";
	node.nodes.push_back(id);

	id_1 = dialog.AddNode(node);

	node.text = "...";
	node.nodes.push_back(id_1);

	id_1 = dialog.AddNode(node);

	// Branch 2
	size_t id_2;

	node.text = "of course, i am famous!";
	node.nodes.push_back(id);
	node.options.push_back("just kidding, never heard of you.");

	id_2 = dialog.AddNode(node);

	// Branch 3
	size_t id_3;

	node.text = "i would never trick you, i am good, i help people!";
	node.nodes.push_back(id);

	id_3 = dialog.AddNode(node);

	node.text = "what? why would i do that?!";
	node.nodes.push_back(id_3);

	id_3 = dialog.AddNode(node);

	// Connect to main branch
	node.text = "i am sure you heard speak of me!";
	node.nodes.push_back(id_1);
	node.options.push_back("uh... no?");

	node.nodes.push_back(id_2);
	node.options.push_back("oh yes I remember");

	node.nodes.push_back(id_3);
	node.options.push_back("are you trying to trick me?");

	id = dialog.AddNode(node);

	node.text = "i am ralph, the mage master!";
	node.nodes.push_back(id);

	id = dialog.AddNode(node);

	node.text = "Hello, fellow human!";
	node.nodes.push_back(id);
	node.options.push_back("Hello?");

	node.nodes.push_back(id);
	node.options.push_back("Who are you?");

	id = dialog.AddNode(node);

	dialog.SetActiveNode(id);
}

void DialogManager::FillDialog_Guard(Dialog& dialog)
{
	// Set dialog box, and font
	dialog.SetPosition(340, 260);
	dialog.SetDialogBg(dialogImg, 600, 206, 20, 20);
	dialog.SetFont(font);

	// Fill the dialog
	DialogNode node;

	size_t id;


	size_t id_2_;


	node.text = "You leave the conversation in the air.";
	id = dialog.AddNode(node);

	node.text = "(quietely)  The things I do for the team...";

	id_2_ = dialog.AddNode(node);

	node.text = "Great, on you go!";
	node.nodes.push_back(id_2_);
	id_2_ = dialog.AddNode(node);

	node.text = "Kill them, if you want to accept the quest, of course";

	node.nodes.push_back(id_2_);
	node.options.push_back("I accept it.");

	node.nodes.push_back(id);
	node.options.push_back("I don't accept the quest.");

	id_2_ = dialog.AddNode(node);




	node.text = "You see those snakes with swords there?";
	node.nodes.push_back(id_2_);
	id_2_ = dialog.AddNode(node);

	node.text = "A questy quest?";
	node.nodes.push_back(id_2_);
	id_2_ = dialog.AddNode(node);

	node.text = "A really worthy quest!";
	node.nodes.push_back(id_2_);
	id_2_ = dialog.AddNode(node);

	size_t id_3_;




	node.text = "You leave the conversation in the air.";
	id = dialog.AddNode(node);

	node.text = "Great! Anyways, a quest for you, blue boy.";
	node.nodes.push_back(id_2_);
	id_3_ = dialog.AddNode(node);

	node.text = "Great! Anyways, a quest for you, red boy.";
	node.nodes.push_back(id_2_);
	id_2_ = dialog.AddNode(node);

	size_t id_1_;

	node.text = "Do you like Red or Blue?";

	node.nodes.push_back(id_2_);
	node.options.push_back("Red.");

	node.nodes.push_back(id_3_);
	node.options.push_back("Blue.");

	node.nodes.push_back(id);
	node.options.push_back("Leave.");

	id_1_ = dialog.AddNode(node);

	node.text = "Questions!";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "...Uhm...";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "Anyways, here i am, i talk, and you respond, i am a completely vehicle NPC, with natural dialogs and...";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "Can you believe it?";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "We could add a sign that lets you know that we have a dialogue system, but it wouldn't count as a NPC just because it has a different tile!";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "Of course i do, i must, else the Matucana Team won’t get the NPC point!";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "Not even a chance to start a conversation.";
	id = dialog.AddNode(node);

	id = dialog.AddNode(node);

	node.text = "...";
	node.nodes.push_back(id_1_);
	node.options.push_back("Do you talk?");

	node.nodes.push_back(id);
	node.options.push_back("Leave.");

	id = dialog.AddNode(node);

	dialog.SetActiveNode(id);
}

void DialogManager::FillDialog_Villager(Dialog& dialog)
{
	// Set dialog box, and font
	dialog.SetPosition(340, 260);
	dialog.SetDialogBg(dialogImg, 600, 206, 20, 20);
	dialog.SetFont(font);

	// Fill the dialog
	DialogNode node;

	size_t id;


	size_t id_2_;


	node.text = "You leave the conversation in the air.";
	id = dialog.AddNode(node);

	node.text = "(quietely)  The things I do for the team...";

	id_2_ = dialog.AddNode(node);

	node.text = "Great, on you go!";
	node.nodes.push_back(id_2_);
	id_2_ = dialog.AddNode(node);

	node.text = "Kill them, if you want to accept the quest, of course";

	node.nodes.push_back(id_2_);
	node.options.push_back("I accept it.");

	node.nodes.push_back(id);
	node.options.push_back("I don't accept the quest.");

	id_2_ = dialog.AddNode(node);




	node.text = "You see those snakes with swords there?";
	node.nodes.push_back(id_2_);
	id_2_ = dialog.AddNode(node);

	node.text = "A questy quest?";
	node.nodes.push_back(id_2_);
	id_2_ = dialog.AddNode(node);

	node.text = "A really worthy quest!";
	node.nodes.push_back(id_2_);
	id_2_ = dialog.AddNode(node);

	size_t id_3_;




	node.text = "You leave the conversation in the air.";
	id = dialog.AddNode(node);

	node.text = "Great! Anyways, a quest for you, blue boy.";
	node.nodes.push_back(id_2_);
	id_3_ = dialog.AddNode(node);

	node.text = "Great! Anyways, a quest for you, red boy.";
	node.nodes.push_back(id_2_);
	id_2_ = dialog.AddNode(node);

	size_t id_1_;

	node.text = "Do you like Red or Blue?";

	node.nodes.push_back(id_2_);
	node.options.push_back("Red.");

	node.nodes.push_back(id_3_);
	node.options.push_back("Blue.");

	node.nodes.push_back(id);
	node.options.push_back("Leave.");

	id_1_ = dialog.AddNode(node);

	node.text = "Questions!";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "...Uhm...";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "Anyways, here i am, i talk, and you respond, i am a completely vehicle NPC, with natural dialogs and...";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "Can you believe it?";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "We could add a sign that lets you know that we have a dialogue system, but it wouldn't count as a NPC just because it has a different tile!";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "Of course i do, i must, else the Matucana Team won’t get the NPC point!";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "Not even a chance to start a conversation.";
	id = dialog.AddNode(node);

	id = dialog.AddNode(node);

	node.text = "...";
	node.nodes.push_back(id_1_);
	node.options.push_back("Do you talk?");

	node.nodes.push_back(id);
	node.options.push_back("Leave.");

	id = dialog.AddNode(node);

	dialog.SetActiveNode(id);
}

//bool DialogManager::LoadDialogs(const char* filename)
//{
//	bool ret = true;
//	SString tmp("%s%s", folder.GetString(), filename);
//
//	pugi::xml_document dialogFile;
//	pugi::xml_parse_result result = dialogFile.load_file(tmp.GetString());
//
//	if (result == NULL)
//	{
//		LOG("Could not load map xml file %s. pugi error: %s", filename, result.description());
//		ret = false;
//	}
//
//	if (ret == true)
//	{
//		// Create and call a private function to load and fill all your map data
//		ret = LoadDialogGroups(dialogFile);
//	}
//
//	return ret;
//}
//
//bool DialogManager::LoadDialogGroups(pugi::xml_node dialogFile)
//{
//	
//	
//	for (pugi::xml_node group = dialogFile.child("dialog_group");
//		group.next_sibling().name() == "dialog_group";
//		group = group.next_sibling())
//	{
//		DialogGroup newDialogGroup;
//		newDialogGroup.name = group.attribute("name").as_string();
//		
//		pugi::xml_node dialog;
//		pugi::xml_node dialogIterator;
//		
//
//		for (dialog = group.child("dialog");
//			dialog.next_sibling().name() == "dialog";
//			dialog = dialog.next_sibling())
//		{
//			if (dialog.attribute("root").as_bool() == true)
//			{
//				//newDialogGroup.dialogNames.push_back(dialog.attribute("value").as_string());
//
//
//				for (pugi::xml_node optionIterator = dialog.child("option");
//					dialog.next_sibling().name() == "option";
//					optionIterator = optionIterator.next_sibling())
//				{
//					LookForChildrenDialogues(group);
//				}
//				
//				
//
//			}
//
//
//		}
//
//		std::vector<Dialog*> dialogs;
//		return true;
//	}
//		
//		
//
//
//
//	
//}
//
//pugi::xml_node DialogManager::LookForChildrenDialogues(pugi::xml_node group)
//{
//	pugi::xml_node ret;
//	for (pugi::xml_node dialogIterator = group.child("dialog");
//		dialogIterator.next_sibling().name() == "dialog";
//		dialogIterator = dialogIterator.next_sibling())
//	{
//
//
//		if (dialogIterator.attribute("root").as_bool() == false)
//		{
//
//			for (pugi::xml_node optionIterator = dialogIterator.child("option");
//				dialogIterator.next_sibling().name() == "option";
//				optionIterator = optionIterator.next_sibling())
//			{
//				LookForChildrenDialogues(group);
//			}
//
//		}
//
//	}
//
//
//
//	return group;
//}
//
//bool DialogManager::AddDialog(Dialog dialog)
//{
//	return 1;
//}