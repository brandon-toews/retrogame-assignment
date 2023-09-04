#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "Screen.h"
#include "MainGame.h"

//Objects created from these classes are used in Screen class
class Player;
class MainGame;

//Class for storing screen dimensions and running methods for displaying stats on screen
class Screen
{
public:
	//Method for displaying player stats that takes in Player class instance in argument
	void const DisplayPlayerStats(Player* plr) const;
	//Method for displaying game stats that takes in MainGame class instance in argument
	void const DisplayGameStats(MainGame* game) const;

	//Default Screen Dimensions
	const static int DISPLAY_WIDTH = 1280;
	const static int DISPLAY_HEIGHT = 720;
	const static int DISPLAY_SCALE = 1;
};