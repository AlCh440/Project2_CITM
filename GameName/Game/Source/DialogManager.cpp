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
	FillDialog_Ranger(dialog_Ranger);
	FillDialog_RangerText(dialog_RangerText);
	FillDialog_Wizard(dialog_Wizard);
	FillDialog_General(dialog_General);
	FillDialog_ArchmageRoom(dialog_ArchmageRoom);
	FillDialog_ArchmageCombat(dialog_ArchmageCombat);


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

	OpenWorldPlayer* player = app->entities->openWorld;
	
	
	if (app->theFall->active)
	{
		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{
			dialog_intro.Finish();
		}

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


		

		

		
		}
	
	if (app->greenPath->active)
	{
		if (dialogActive_Ranger)
		{
			if ((!dialog_Ranger.Finished()))
			{
				if (player != nullptr) player->SetMotion(false);
				dialog_Ranger.Update();
			}
			else
			{
				if (player != nullptr) player->SetMotion(true);
				dialogActive_Ranger = false;
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

		if (dialogActive_RangerText)
		{
			if ((!dialog_RangerText.Finished()))
			{
				if (player != nullptr) player->SetMotion(false);
				dialog_RangerText.Update();
			}
			else
			{
				if (player != nullptr) player->SetMotion(true);
				dialogActive_RangerText = false;
			}
		}

		if (dialogActive_Wizard)
		{
			if ((!dialog_Wizard.Finished()))
			{
				if (player != nullptr) player->SetMotion(false);
				dialog_Wizard.Update();
			}
			else
			{
				if (player != nullptr) player->SetMotion(true);
				dialogActive_Wizard = false;
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

	if (app->generalRoom->active)
	{
		if (dialogActive_General)
		{
			if ((!dialog_General.Finished()))
			{
				if (player != nullptr) player->SetMotion(false);
				dialog_General.Update();
			}
			else
			{
				if (player != nullptr) player->SetMotion(true);
				dialogActive_General = false;
			}
		}
	}

	if (app->dragonCliff->active)
	{
		if (dialogActive_ArchmageCombat)
		{
			if ((!dialog_ArchmageCombat.Finished()))
			{
				if (player != nullptr) player->SetMotion(false);
				dialog_ArchmageCombat.Update();
			}
			else
			{
				if (player != nullptr) player->SetMotion(true);
				dialogActive_ArchmageCombat = false;
			}
		}
	}

	if (app->mageRoom->active)
	{
		if (dialogActive_ArchmageRoom)
		{
			if ((!dialog_ArchmageRoom.Finished()))
			{
				if (player != nullptr) player->SetMotion(false);
				dialog_ArchmageRoom.Update();
			}
			else
			{
				if (player != nullptr) player->SetMotion(true);
				dialogActive_ArchmageRoom = false;
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

void DialogManager::FillDialog_Ranger(Dialog& dialog)
{
	dialog.SetPosition(340, 260);
	dialog.SetDialogBg(dialogImg, 600, 206, 20, 20);
	dialog.SetFont(font);

	// Fill the dialog
	DialogNode node;

	size_t id;

	size_t id_5_;
	
	node.text = "I can definitely shoot from a safe distance!";

	id_5_ = dialog.AddNode(node);

	node.text = "But with that head of your’s !";
	node.nodes.push_back(id_5_);
	id_5_ = dialog.AddNode(node);

	node.text = "Great, but we should go and find the mague first, but these damn enemies don’t let me go forth!";
	node.nodes.push_back(id_5_);
	id_5_ = dialog.AddNode(node);

	

	size_t id_4_;
	size_t id_2_;

	node.text = "Let's give it a go.";

	id_2_ = dialog.AddNode(node);

	node.text = "That Buckethead of yours can take while i shoot em";
	node.nodes.push_back(id_2_);
	id_2_ = dialog.AddNode(node);

	node.text = "The problem is that ahead there are some enemies, and I couldn't beat ' em alone, but now, with you?";
	node.nodes.push_back(id_2_);
	id_2_ = dialog.AddNode(node);

	node.text = "Like what were we doing in the first place, anyways we should find the mague first, maybe he remembers all.";
	node.nodes.push_back(id_2_);
	id_2_ = dialog.AddNode(node);

	node.text = "I am your team mate, I still remember that, and that we were with a mague too, but I also forgot the other things…";
	node.nodes.push_back(id_2_);
	id_2_ = dialog.AddNode(node);

	node.text = "Uhm, I hoped that your bucket head would have protected you from the impact, but now I see that you are even more clueless than me.";
	node.nodes.push_back(id_2_);
	id_2_ = dialog.AddNode(node);

	node.text = "Do you remember me or not!?";

	node.nodes.push_back(id_2_);
	node.options.push_back("Never seen you before…");

	node.nodes.push_back(id_5_);
	node.options.push_back("Forget it, I remember you now…");

	id_4_ = dialog.AddNode(node);

	node.text = "Are you going to concentrate on that Buckethead? Concentrate on the things we have to do!";
	node.nodes.push_back(id_4_);

	id_4_ = dialog.AddNode(node);

	size_t id_3_;

	
	
	node.text = "Let’s give it a go!";

	id_3_ = dialog.AddNode(node);

	node.text = "Uhm, maybe we can find him if we seek a little more, we should get past these enemies first. We can beat 'em together!";
	node.nodes.push_back(id_3_);

	id_3_ = dialog.AddNode(node);
	



	//size_t id_2_;
	
	
	
	node.text = "Let's give it a go.";

	id_2_ = dialog.AddNode(node);

	node.text = "That Buckethead of yours can take while i shoot em";
	node.nodes.push_back(id_2_);
	id_2_ = dialog.AddNode(node);

	node.text = "The problem is that ahead there are some enemies, and I couldn't beat ' em alone, but now, with you?";
	node.nodes.push_back(id_2_);
	id_2_ = dialog.AddNode(node);
	
	node.text = "Like what were we doing in the first place, anyways we should find the mague first, maybe he remembers all.";
	node.nodes.push_back(id_2_);
	id_2_ = dialog.AddNode(node);
	
	node.text = "I am your team mate, I still remember that, and that we were with a mague too, but I also forgot the other things…";
	node.nodes.push_back(id_2_);
	id_2_ = dialog.AddNode(node);

	node.text = "Uhm, I hoped that your bucket head would have protected you from the impact, but now I see that you are even more clueless than me.";
	node.nodes.push_back(id_2_);
	id_2_ = dialog.AddNode(node);

	node.text = "Have you forgotten about me?";

	node.nodes.push_back(id_2_);
	node.options.push_back("Never seen you before…");

	node.nodes.push_back(id_5_);
	node.options.push_back("Forget it, I remember you now…");

	

	id_2_ = dialog.AddNode(node);


	node.text = "The only unic, the ranger?";
	node.nodes.push_back(id_2_);
	id_2_ = dialog.AddNode(node);

	node.text = "Hello? Is it me?";
	node.nodes.push_back(id_2_);
	id_2_ = dialog.AddNode(node);

	node.text = "Uhm…";
	node.nodes.push_back(id_2_);
	id_2_ = dialog.AddNode(node);

	size_t id_1_;

	
	node.text = "Aniways, seen the pointy hat anywhere Buckethead?";

	node.nodes.push_back(id_2_);
	node.options.push_back("You are?");

	node.nodes.push_back(id_3_);
	node.options.push_back("Haven’t seen him…");

	node.nodes.push_back(id_4_);
	node.options.push_back("You called me what?");

	node.nodes.push_back(id);
	node.options.push_back("Leave.");

	id_1_ = dialog.AddNode(node);


	node.text = "Wow,  thought you where dead!";

	node.nodes.push_back(id_1_);
	node.options.push_back("Do you talk?");

	node.nodes.push_back(id);
	node.options.push_back("Leave.");
	
	id = dialog.AddNode(node);
	
	dialog.SetActiveNode(id);
}

void DialogManager::FillDialog_RangerText(Dialog& dialog)
{
	dialog.SetPosition(340, 260);
	dialog.SetDialogBg(dialogImg, 600, 206, 20, 20);
	dialog.SetFont(font);

	// Fill the dialog
	DialogNode node;

	size_t id;

	size_t id_1_;
	
	node.text = "Necessities of the story…";
	//node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);
	
	id_1_ = dialog.AddNode(node);

	node.text = "It’s the pointy hat, right there with the guard on the castle!";

	node.nodes.push_back(id_1_);
	node.options.push_back("How can you see him from here?");

	node.nodes.push_back(id);
	node.options.push_back("Leave.");

	id = dialog.AddNode(node);

	node.text = "Hey look!";
	node.nodes.push_back(id);
	id= dialog.AddNode(node);

	dialog.SetActiveNode(id);


}
void DialogManager::FillDialog_Wizard(Dialog& dialog)
{
	dialog.SetPosition(340, 260);
	dialog.SetDialogBg(dialogImg, 600, 206, 20, 20);
	dialog.SetFont(font);

	// Fill the dialog
	DialogNode node;

	size_t id;

	size_t id_1_;

	node.text = "It’s around this corner on the first door, these good guards allowed us to pass, so let’s get to it.";
	//node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "We should talk with the archmage of these villages, but first we must be granted permission, so we have to go to the general office first.";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "None of us remember anything aside from the fact that we were a team.";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "Wizard: So let me get these straight";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "There you go player, now you can listen to the important part!";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "Oh whoops, almost skip the important part!";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "(Advances time forward)";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "Let's see...";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "Uhm...";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);
	
	node.text = "Some boring presentations after";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "Narrator: Yara Yara...";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);
	
	node.text = "Wizard: Then stop calling me weird names and call me what i am!";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);
	
	node.text = "Ranger: That was rude";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);
	
	node.text = "Wizard: Dumbass!";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);
	
	node.text = "Ranger: Pointy Hat!";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);
	
	node.text = "Wizard: But I was just about to tell you about the irony of the best attack and defence phrase!";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);
	
	node.text = "Guard: Just go ahead already, i shouldn't have talked with a wizard, shud have seen these monolog coming.";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "Wizard: So! As I told you, the mere fact of an arrow on the knee shouldn't stop you from making adventures!";
	node.nodes.push_back(id_1_);
	//id_1_ = dialog.AddNode(node);

	id_1_ = dialog.AddNode(node);

	node.text = "...";
	node.nodes.push_back(id_1_);
	node.options.push_back("Do you talk?");

	node.nodes.push_back(id);
	node.options.push_back("Leave.");

	id = dialog.AddNode(node);

	dialog.SetActiveNode(id);
	
}

void DialogManager::FillDialog_General(Dialog& dialog)
{
	dialog.SetPosition(340, 260);
	dialog.SetDialogBg(dialogImg, 600, 206, 20, 20);
	dialog.SetFont(font);

	// Fill the dialog
	DialogNode node;

	size_t id;

	size_t id_1_;
	node.text = "If you return victorious, go and speak with the archmage.";
	//node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "Wizard: Deal, not like we have many options.";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "General: Uhm, let’s make a deal, you get rid of the goblin problem we have in these caves and I grant you access to the archmage room, deal ?";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "Wizard: Oh, no no, we just happen to have lost grate part of our memory, and we need to talk with your local sorcerer, and see if he can do something about it";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "General: Yes, your banner is from that kingdom, or did you steal it?";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "Narrator: We don’t talk about these players, just don’t mind it…";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "Wizard: The RPG kingdom?";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "General: Greetings travellers, what tubes bring a party to the RPG kingdom here?";
	node.nodes.push_back(id_1_);

	id_1_ = dialog.AddNode(node);

	node.text = "...";
	node.nodes.push_back(id_1_);
	node.options.push_back("Do you talk?");

	node.nodes.push_back(id);
	node.options.push_back("Leave.");

	id = dialog.AddNode(node);

	dialog.SetActiveNode(id);
}

void DialogManager::FillDialog_ArchmageRoom(Dialog& dialog)
{
	dialog.SetPosition(340, 260);
	dialog.SetDialogBg(dialogImg, 600, 206, 20, 20);
	dialog.SetFont(font);

	// Fill the dialog
	DialogNode node;

	size_t id;

	size_t id_1_;
	
	node.text = "You may go now.";
	//node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "Archmage: We have a portal, we mainly use it to contact distant kingdoms, but after the aid you provided to the village, I will arrange it so you can travel to the future.";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "Knight: Is there a way to return to our duty ?";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "Archmage: I don't know, maybe he has fun doing that.";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "Wizard: Why would he do that, why not only kill us?";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "But as you see, you didn't succeed, he sent you all to the past and stripped your memories away.";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "Archmage: Well, you weren't sent to the past alone, you were meant to defeat an enemy, in order to reclaim its powers and save the world from imminent annihilation.";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "Wizard: That solves one question, but why don't we remember anything ?";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "Archmage: 2000";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "Knight: What year are we in ?";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "Archmage: No, I said it properly, you are all in the wrong time, in fact you are from the year 2077 to be precise";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "Wizard: We were you mean ?";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "Well, yes, you are from said kingdom, but you are going to be sent here for a reason";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "Archmage: …";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "Ranger: Oh, and we recently learned that we are from the RPG kingdom";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "Knight: We know each other…";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "What can you recall ?";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "Archmage: Save it for another person, i know you are all lost and need help, i will aid you on that.";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "Wizard: Greetings fellow lite…";
	node.nodes.push_back(id_1_);

	id_1_ = dialog.AddNode(node);

	node.text = "...";
	node.nodes.push_back(id_1_);
	node.options.push_back("Do you talk?");

	node.nodes.push_back(id);
	node.options.push_back("Leave.");

	id = dialog.AddNode(node);

	dialog.SetActiveNode(id);
}

void DialogManager::FillDialog_ArchmageCombat(Dialog& dialog)
{
	dialog.SetPosition(340, 260);
	dialog.SetDialogBg(dialogImg, 600, 206, 20, 20);
	dialog.SetFont(font);

	// Fill the dialog
	DialogNode node;

	size_t id;

	size_t id_1_;

	node.text = "I beat you all once, I will do it again.";
	//node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "Archmage: And if you don't, I will make sure it stays that way the next time we fight.";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "Archmage/Narrator: I suppose you already saw it coming";
	node.nodes.push_back(id_1_);
	id_1_ = dialog.AddNode(node);

	node.text = "Narrator: And here the party lies, in front of their saviour, guide and enemy, the Archmage.";
	node.nodes.push_back(id_1_);

	id_1_ = dialog.AddNode(node);

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