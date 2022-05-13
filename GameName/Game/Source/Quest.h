#pragma once
#include"SString.h"
#include "PugiXml/src/pugixml.hpp"
#include "SDL/include/SDL.h"

class Quest
{

public:
	enum QuestProgress { NOT_AVAILABLE, AVAILABLE, ACTIVE, COMPLETE, DONE }; //States a quest can have


	int id;							//Quest identification
	QuestProgress progress;			//State of the current quest 
	int nextQuest;					//next quest, if there is any (chain quest)

	int progression;					//Posible quest objectives
	int reward;						//Posible quest rewards
	int amount;

	SString title;					//Title for the quest
	SString description;			//What player has to know about the quest
	SString objective;				// Clear objective for the player

	SDL_Texture* titleTex;
	SDL_Texture* descriptionTex;
	SDL_Texture* objectiveTex;

	int coinsReward;
	// add item reward?

	SDL_Rect rTitle, rDescription, rObjective;

	//// Load / Save
	//virtual bool LoadState(pugi::xml_node&);
	//virtual bool SaveState(pugi::xml_node&) const;

};

