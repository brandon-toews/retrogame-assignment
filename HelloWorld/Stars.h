#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "Screen.h"
#include "Lasers.h"
using namespace std;

//Objects created from these classes are used in Stars class
class Player;
class Lasers;
class MainGame;

//Stars Class storing each indivual star and running methods to create, move, and screenwrap stars
class Stars
{
public:
	
	//Method for creating stars(spikeballs), takes in time in arguments
	void const CreateStars( float time );
	//Method for moving already created stars(spikeballs), takes in instances of player, lasers, and maingame in arguments
	void const MoveStars( Player* plr1, Lasers* lasers, MainGame* game );
	//Method for screen wrapping stars that are leaving screen, takes in star game object in arguments
	void const StarScreenWrap( GameObject& star ) const;

	//struct for creating each individual star while storing its specific attributes
	struct iStar
	{
		//enum for star(spikeball) state
		enum StarState
		{
			NORMAL = 0,
			YARN,
			DESTROYED
		};

		//Variable to store game object ID set during creation in create star method
		int starID = NULL;
		//Star velocity for each individual star set during creation in create star method
		Point2f starVelocity = { 0, 0 };
		//Star speed for each individual star set during creation in create star method
		float starSpeed = 0.0f;
		//Star angle for each individual star set during creation in create star method, used to calculate star velocity
		float angle = 0.0f;
		//Star rotation speed for each individual star set based on angle, also set during move star method to control star rotation speed depending on any changes in angle
		float rotationSpeed = 0.1f;//angle * 0.05f;
		//variable to store during what level star was destroyed so that is can be changed back to NORMAL if player advances to next level
		int levelDestroyed = 0;
		//Default star state is NORMAL
		StarState state = NORMAL;
	};

	//vector of individual stars that have been created
	vector<iStar> starsArray;
	//Default number of stars on screen at one time
	int numOfStars = 5;
	//clock to stagger creation on stars so they don't all show up at once
	float releaseTime = 0.0f;
};

