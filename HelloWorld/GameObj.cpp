#include "GameObj.h"
#define PLAY_IMPLEMENTATION

//Method for checking if the exact image of the laser connects with player
bool const GameObj::Collide(GameObject& obj1, GameObject& obj2)
{
		//Checks if any part of the laser image matches with any part of the player image on x-axis 
		if ((obj1.startMatrix.x >= obj2.startMatrix.x) && (obj1.startMatrix.x <= obj2.endMatrix.x) || (obj1.endMatrix.x >= obj2.startMatrix.x) && (obj1.endMatrix.x <= obj2.endMatrix.x))
		{
			//Checks if any part of the laser image matches with any part of the player image on y-axis 
			if ((obj1.startMatrix.y >= obj2.startMatrix.y) && (obj1.startMatrix.y <= obj2.endMatrix.y) || (obj1.endMatrix.y >= obj2.startMatrix.y) && (obj1.endMatrix.y <= obj2.endMatrix.y))
			{
				//If both conditions are met then laser is colliding with player, return true
				return true;
			}
			//If second condition isn't met then laser is not colliding with player, return false
			return false;
		}
	//If first condition isn't met then laser is not colliding with player, return false
	return false;
}