#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "Stars.h"
#include "Lasers.h"
#include "Screen.h"
#include "Player.h"
#include "PowerUps.h"
#include "Menu.h"
#include "Splash.h"
#include <iostream>
#include <string>
#include <math.h>
using namespace std;

//Objects created from these classes are used in MainGame class
class PowerUps;
class Menu;

//Class for storing information about the game and updating levels and resetting game
class MainGame
{
public:
	
	//Method for updating the level when player chooses a specific level or advances to a new level
	void const UpdateLevel(float time);
	//Method for resetting objects in game when it has been restarted
	void const ResetGame();

	//enum for game states
	enum State
	{
		SPLASH,
		STARTMENU,
		PLAY,
		NEWLEVEL,
		PAUSE,
		GAMEOVER,
		WIN
	};

	//enum for menu state
	enum MenuNav
	{
		MAIN,
		SETTINGS,
		DIFF,
		LEVEL,
		PAUSED
	};

	//enum for difficulty setting
	enum Difficulty
	{
		EASY,
		NORMAL,
		HARD
	};

	//struct for saving the games timer, level, and game/menu/difficulty states
	struct Game
	{
		//Starts with timer at 0
		float timer = 0;
		//Starts at level 1 unless a different level is selected
		int level = 1;
		//Starts at game state SPLASH for Splash screen
		State state = SPLASH;
		//Menu state set at MAIN for main menu to begin with
		MenuNav whichMenu = MAIN;
		//Difficulty state set at NORMAL
		Difficulty difficulty = NORMAL;
	};
	//One struct called game to store everything
	Game game;

	//clock for
	//float releaseClock = 0.0f;
	//Variable that stores how long each level lasts
	float levelTime = 20.0f;
};