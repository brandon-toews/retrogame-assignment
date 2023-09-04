#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "Screen.h"
#include "GameObj.h"
#include "MainGame.h"
using namespace std;

//Objects created from these classes are used in Lasers class
class Player;
class Stars;
class MainGame;

//Class for creating, moving, and resetting lasers
class Lasers
{
public:

	//Method for creating lasers and initializing beginning attributes
	void const CreateLasers(float elapsedTime);

	//Method for moving already created lasers. Handles collisions with player and stars with reflected lasers
	void const MoveLasers(Player* plr1, Stars* stars, MainGame* game);

	//Resets laser position to top of screen
	void const ResetLaserPos(GameObject& laser) const;

	//Struct for creating each individual laser with its own stored attributes
	struct iLaser
	{
		//State of laser
		enum LaserState
		{
			NORMAL = 0,
			REFLECTED,
			DESTROYED
		};

		//Laser ID which is the sprite ID stored upon creation
		int laserID = NULL;

		//Each laser starts with NORMAL state
		LaserState state = NORMAL;

		//Each laser starts with 0 angle which means it will go straight down
		float angle = 0.0f;

		//Each laser stores when it was destroyed so that if the player advances to the next level it will be changed back to NORMAL state
		int levelDestroyed = 0;

		//Each laser starts with 0 velocity but is given a velocity in the CreateLasers method
		Point2f laserVelocity = { 0, 0 };
	};

	//Each instance of Lasers class is given...
	
	//A vector of iLaser structs(a vector of individual lasers)
	vector<iLaser> lasersArray;

	//A variable to store how many individual lasers to manage
	int numOfLasers = 30;

	//A variable to control the speed of all the lasers
	float laserSpeed = 3.0f;

	//A release time that staggers the creation of lasers so they have better spacing
	float releaseTime = 0.1f;

};
