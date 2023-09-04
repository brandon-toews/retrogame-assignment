#include "Lasers.h"
#define PLAY_IMPLEMENTATION
using namespace std;

//Clock that is used to stagger the creation of lasers so they have better spacing
static float laserTime;

//CreateLasers method that sizes the lasersArray according to numofLasers, creates the Game Object and initializes some of the attributes of the laser
 void const Lasers::CreateLasers( float elapsedTime )
{
	//Increment clock with elapsedTime
	laserTime += elapsedTime;

	//If lasersArray doesn't already match how many lasers are supposed to exist then create laser
	if (lasersArray.size() <= numOfLasers)
	{
		//Loop thru each laser that should be created
		for (int i = 0; i <= numOfLasers; i++)
		{
			//Only create a laser if it hasn't already been created and laserTime has reached the releaseTime interval
			if (i > lasersArray.size() && laserTime > releaseTime)
			{
				//Add another element to vector
				lasersArray.push_back(iLaser());
				//Create game object and store its sprite ID in laserID variable, give it a random spot on x-axis and always at the top of y-axis
				lasersArray[i - 1].laserID = Play::CreateGameObject(GameObj::TYPE_LASER, { (rand() % Screen::DISPLAY_WIDTH), 0 }, 30, "laser");
				//Individual laser velocity is calculated based on its stored angle and laserSpeed, because all lasers are initialized with 0 angle they all start by going down
				lasersArray[i - 1].laserVelocity = { laserSpeed * sin(lasersArray[i - 1].angle),  laserSpeed * cos(lasersArray[i - 1].angle) };
				//reset laserTime so the next laser isn't created right away
				laserTime = 0;
			}
		}
	}
}

// Move Lasers method used to move lasers and handle collisions with stars and player. Also handle laser states and changes laser movement based on game state.
void const Lasers::MoveLasers(Player* plr1, Stars* stars, MainGame* game)
{
	//Capture player game object
	GameObject& obj_Player = Play::GetGameObjectByType(GameObj::TYPE_PLAYER);

	//Loop thru all lasers that have been created
	for (int i = 0; i < lasersArray.size(); i++)
	{
		//Capture laser game object using stored ID in laserID variable
		GameObject& obj_Laser = Play::GetGameObject(lasersArray[i].laserID);
		//switch statement for handling laser movement based on game state
		switch (game->game.state)
		{
		//If game state is in PLAY
		case MainGame::PLAY:
				//Set game object velocity to velocity stored in the individual laser's laserVelocity variable
				obj_Laser.velocity = lasersArray[i].laserVelocity;

				//switch statement for handling laser image and star collisions based on its state
				switch (lasersArray[i].state)
				{
				//If laser's state is NORMAL
				case iLaser::LaserState::NORMAL:

					//Set lasers image to the standard laser image
					Play::SetSprite(obj_Laser, "laser", 0.0f);
					//Update and draw laser with no rotation and normal image
					Play::UpdateGameObject(obj_Laser);
					Play::DrawObject(obj_Laser);

					//If laser collides with player using custom collide method in GameObj class
					if (GameObj::Collide(obj_Laser, obj_Player))
					{
						//switch statement for handling laser collision based on player's state
						switch (plr1->state)
						{
						//If player state is SHIELED
						case Player::SHIELDED:
							Play::PlayAudio("laserReflect");
							//Set players laserHitClock to 0 so that the player image changes to laser hit image
							plr1->laserHitClock = 0.0f;
							//Set laser's image to the reflected laser image
							Play::SetSprite(obj_Laser, "reflectedlaser", 0.0f);
							//Set laser's state to REFLECTED
							lasersArray[i].state = iLaser::LaserState::REFLECTED;
							//Calculate angle that the last hit the player at and then set that as the laser's angle
							lasersArray[i].angle = atan2(obj_Laser.pos.x - obj_Player.pos.x, -(obj_Laser.pos.y - obj_Player.pos.y));
							//Set laser game object's rotation to the angle stored
							obj_Laser.rotation = lasersArray[i].angle;
							//Individual laser velocity is calculated based on its stored angle and laserSpeed, because the laser angle has changed laser will be rotated to match angle and will travel a set speed in that direction
							lasersArray[i].laserVelocity = { laserSpeed * sin(lasersArray[i].angle),  laserSpeed * -cos(lasersArray[i].angle) };
							break;

						//If player state is NORMAL or CAT
						default:
							Play::PlayAudio("laserHitNormal");
							//Subtract to health from player
							plr1->health -= 10;
							//If health drops below 0
							if (plr1->health <= 0)
							{
								//Set player health to 0 so that it can't be in the negatives
								plr1->health = 0;
								//Set player state to DEAD
								plr1->state = Player::DEAD;
							}
							//Set players laserHitClock to 0 so that the player image changes to laser hit image
							plr1->laserHitClock = 0.0f;
							//Reset lasers position to top of screen
							ResetLaserPos(obj_Laser);
							break;
						}
					}
					//If NORMAL laser is leaving screen
					else if (Play::IsLeavingDisplayArea(obj_Laser))
					{
						//Reset lasers position to top of screen
						ResetLaserPos(obj_Laser);
					}
					break;

				//If laser's state is REFLECTED
				case iLaser::LaserState::REFLECTED:
					//Loop through all stars that have been created
					for (int p = 0; p < stars->starsArray.size(); p++)
					{
						//Captures star Game Object using using stored ID in starID variable
						GameObject& obj_Star = Play::GetGameObject(stars->starsArray[p].starID);
						//If laser and star are colliding and the star isn't already in a DESTROYED state
						if (GameObj::Collide(obj_Laser, obj_Star) && stars->starsArray[p].state != Stars::iStar::DESTROYED)
						{
							//Set this star to DESTROYED state
							stars->starsArray[p].state = Stars::iStar::DESTROYED;
							//Store the level star was DESTROYED at so that if player advances to next level star will be set back to NORMAL
							stars->starsArray[p].levelDestroyed = game->game.level;

							//Add 50 to player score for destroying star
							plr1->score += 50;
						}
					}
					//Update and draw laser with rotation and reflected laser image that was set when player collides with laser when player in SHIELD state
					Play::UpdateGameObject(obj_Laser);
					Play::DrawObjectRotated(obj_Laser);

					//If REFLECTED laser is leaving screen
					if (Play::IsLeavingDisplayArea(obj_Laser))
					{
						//Reset lasers position to top of screen
						ResetLaserPos(obj_Laser);
						//Set angle to 0 so laser goes down
						lasersArray[i].angle = 0.0f;
						//Set laser game object's rotation to the angle stored
						obj_Laser.rotation = lasersArray[i].angle;
						//Set laser's state to NORMAL
						lasersArray[i].state = iLaser::LaserState::NORMAL;
						//Individual laser velocity is calculated based on its stored angle and laserSpeed, because angle was just set to 0 it will go down
						lasersArray[i].laserVelocity = { laserSpeed * sin(lasersArray[i].angle), laserSpeed * cos(lasersArray[i].angle) };
					}
					break;

				//If laser's state is DESTROYED
				case iLaser::LaserState::DESTROYED:
					//Keep updating its location but don't draw it or handle collisions
					Play::UpdateGameObject(obj_Laser);
					//If DESTROYED laser is leaving screen and player is still on the same level that it was destroyed
					if (Play::IsLeavingDisplayArea(obj_Laser) && lasersArray[i].levelDestroyed == game->game.level)
					{
						//Reset lasers position to top of screen
						ResetLaserPos(obj_Laser);
					}
					//If DESTROYED laser is leaving screen and player has advanced levels from the level the laser was destroyed on
					else if (Play::IsLeavingDisplayArea(obj_Laser) && lasersArray[i].levelDestroyed < game->game.level)
					{
						//Reset lasers position to top of screen
						ResetLaserPos(obj_Laser);
						//Set laser's state to NORMAL
						lasersArray[i].state = iLaser::LaserState::NORMAL;
						//Update laser object with new location
						Play::UpdateGameObject(obj_Laser);
					}
					break;
				//If laser's state is set to nothing then do nothing as default
				default:
					break;
				}
			break;

		//If game state is PAUSED, NEWLEVEL, or GAMEOVER
		default:
			//switch statement for handling laser image and movement based on lasers state
			switch (lasersArray[i].state)
			{
			//If laser's state is NORMAL
			case iLaser::LaserState::NORMAL:
				//Just draw laser with 0 angle without changing position
				Play::DrawObject(obj_Laser);
				break;

			//If laser's state is REFLECTED
			case iLaser::LaserState::REFLECTED:

				//Just draw reflected laser with angle without changing position
				Play::DrawObjectRotated(obj_Laser);
				break;

			//Don't draw laser if its state is DESTROYED or isn't set
			default:
				break;
			}
			break;
		}
	}
}

//Method for resetting laser's postion to top of screen and random point on x-axis
void const Lasers::ResetLaserPos(GameObject& laser) const
{
	//give laser game object a random spot on x-axis and always at the top of y-axis
	laser.pos = { rand() % Screen::DISPLAY_WIDTH, 0 };
}

