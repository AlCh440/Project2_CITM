#include "WorldTestScene.h"
#include "Log.h"
#include "App.h"
#include "Map.h"
#include "Entities.h"
#include "Audio.h"
#include "Physics.h"
#include "DialogFonts.h"

WorldTestScene::WorldTestScene(bool isActive) : Module(isActive)
{
	name.Create("World Test Scene");
}

WorldTestScene::~WorldTestScene()
{
}

bool WorldTestScene::Awake(pugi::xml_node&)
{


	return true;
}

bool WorldTestScene::Start()
{
	LOG("Loading World Test");


	app->physics->Start();
	app->map->Load("WorldMapTest.tmx");
	app->entities->Start();

	

	//test dialog

	FillDialog(dialog);
	return true;
}

bool WorldTestScene::PreUpdate()
{
	return true;
}

bool WorldTestScene::Update(float dt)
{
	
	if (!dialog.Finished()) 
	{
		dialog.Update();
	}
	return true;
}

bool WorldTestScene::PostUpdate()
{
	app->map->Draw();
	return true;
}

bool WorldTestScene::CleanUp()
{
	app->map->CleanUp();
	app->entities->CleanUp();
	app->physics->CleanUp();
	app->audio->StopMusic();
	return true;
}

void WorldTestScene::FillDialog(Dialog& dialog)
{
	// Take dialog box, and font
	SDL_Texture* dialogImg = app->tex->Load("Assets/Textures/dialog_box_paper.png");

	//char lookupTable[] = { "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890 " };
	char lookupTable[] = { "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[�]��!���%&'()*+,-.^0123456789:;<=>?/abcdefghijklmnopqrstuvwxyz �������" };


	int font = app->dialogFonts->Load("Assets/Fonts/font1_black_1.png", lookupTable, 6);

	// Set dialog box, and font
	dialog.SetPosition(414, 220);
	dialog.SetDialogBg(dialogImg, 453, 206, 20, 20);
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