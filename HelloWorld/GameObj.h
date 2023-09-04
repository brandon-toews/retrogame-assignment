#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "Screen.h"
#include "Lasers.h"

//Game object class to provide one centralized enum for creating game objects and a custom Collide method for the lasers
class GameObj
{
public:

	//Enum type for each object in game
	enum GameObjectType
	{
		TYPE_NULL = -1,
		TYPE_STAR,
		TYPE_LASER,
		TYPE_POWERUP,
		TYPE_PLAYER,
	};

	//Method for checking if the exact image of the laser connects with player
	bool static const Collide(GameObject& obj1, GameObject& obj2);
};

