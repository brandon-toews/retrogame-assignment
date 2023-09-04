#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "Screen.h"
#include "GameObj.h"
#include "MainGame.h"

//Objects created from these classes are used in PowerUps class
class Player;
class MainGame;

//Class for storing 2 powerup types and creating and moving powerups with methods
class PowerUps
{
public:
	//Default y-axis start postion for powerups
	int const yPos = -50;

	//Method for creating power ups
	void const CreatePowerUps();
	//Method for moving powerups and handling collisions with player
	void const MovePowerUps(float elapsedTime, Player* plr1, MainGame* game);

	//struct for creating individual powerups
	struct iPowerUp
	{
		//variable for storing game object ID that is stored during create powerup method
		int ID = NULL;
		//default speed the powerup travels at
		int powerUpSpeed = 5;
		//clock to track when power up should be released
		float releaseClock = 0.0f;
	};

	//create to instances of individual power up struct, one for shield and one for cat powerups
	iPowerUp shield, cat;

};

