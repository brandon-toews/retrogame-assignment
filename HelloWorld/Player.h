#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "Screen.h"
#include "Lasers.h"

//Objects created from MainGame class are used in Player class
class MainGame;

//Player is used to store player attribute and call create and move player methods
class Player
{

public:
	//enum for different states player can be in
	enum PlayerState
	{
		NORMAL = 0,
		SHIELDED,
		CAT,
		DEAD
	};

	//Game object ID is stored here when created
	int playerID = NULL;
	//How many spaces the player moves
	int const spaces = 4;
	//Default health
	int health = 100;
	//Default score
	int score = 0;
	//Default player state is NORMAL
	PlayerState state = NORMAL;
	//Clock for keeping track of how long player has been in powerup state
	float powerUpClock = 0.0f;
	//laser hit clock used to change player image when player has been hit by laser
	float laserHitClock = 0.5f;
	//star hit clock used to change player image when player has been hit by star
	float spikeballHitClock = 0.5f;

	int lastStarHit = NULL;

	//Method for creating player game object
	void const CreatePlayer();
	//Method for moving player game object
	void const MovePlayer(float elapsedTime, MainGame* game);
};

