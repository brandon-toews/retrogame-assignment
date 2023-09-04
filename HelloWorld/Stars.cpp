#include "Stars.h"
#define PLAY_IMPLEMENTATION

//Method for creating stars(spikeballs), takes in time in arguments
void const Stars::CreateStars( float time )
{
	//Increment clock with elapsedTime
	releaseTime += time;
	//If starsArray doesn't already match how many stars are supposed to exist then create star
	if (starsArray.size() <= numOfStars)
	{
		//Loop thru each star that should be created
		for (int i = 0; i <= numOfStars; i++)
		{
			//Only create a laser if it hasn't already been created and laserTime has reached the releaseTime interval
			if (i > starsArray.size() && releaseTime > 0.1f)
			{
				//Add another element to vector
				starsArray.push_back(iStar());
				//Create game object and store its sprite ID in starID variable, give it a random spot on y-axis and always at 0 on x-axis
				starsArray[i - 1].starID = Play::CreateGameObject(GameObj::TYPE_STAR, { 0, rand() % Screen::DISPLAY_HEIGHT }, 30, "spikeball");
				//Set a random star speed for this individual star
				starsArray[i - 1].starSpeed = (rand() % 6) + 1;
				//Set a random angle for this individual star
				starsArray[i - 1].angle = (rand() % 2) + 1;
				//every other star created make the angle negative, this makes it so each star isn't headed the same direction
				if (starsArray.size() % 2 == 0) starsArray[i - 1].angle = -starsArray[i - 1].angle;
				//Individual star velocity is calculated based on its stored angle and starSpeed
				starsArray[i - 1].starVelocity = { starsArray[i - 1].starSpeed * sin(starsArray[i - 1].angle),  starsArray[i - 1].starSpeed * -cos(starsArray[i - 1].angle) };
			
				//reset release clock so the next star isn't created right away
				releaseTime = 0.0f;
			}
		}
	}

}

//Method for moving already created stars(spikeballs), takes in instances of player, lasers, and maingame in arguments
void const Stars::MoveStars(Player* plr1, Lasers* lasers, MainGame* game)
{
	//Loop thru each star that has been created
	for (int i = 0; i < starsArray.size(); i++)
	{
		//capture star game object using stored star ID
		GameObject& obj_Star = Play::GetGameObject(starsArray[i].starID);
		//Set rotation speed in case angle has changed since last time
		starsArray[i].rotationSpeed += starsArray[i].angle * 0.05f;
		//Set game objects velocity to the velocity stored in the individual stars attributes
		obj_Star.velocity = starsArray[i].starVelocity;
		//Set game objects rotation based on changes to rotation speed
		obj_Star.rotation = starsArray[i].rotationSpeed;

		//If Star isn't in DESTROYED state handle movements and collisions
		if (starsArray[i].state != iStar::StarState::DESTROYED)
		{
			//Switch statement based on player state to return stars back to NORMAL state if player no longer has cat power up
			switch (plr1->state)
			{
			//If has cat power up do nothing to star state
			case Player::CAT:
				//do nothing
				break;
			//if Player has shield power up or no power up
			default:
					//change star state back to NORMAL
					starsArray[i].state = iStar::StarState::NORMAL;
				break;
			}

			//Capture player game object using stored Player ID
			GameObject& obj_Player = Play::GetGameObject(plr1->playerID);
			//Switch statement based on game state
			switch (game->game.state)
			{
			//if game state is in PLAY handle star movements and collisions 
			case MainGame::PLAY:

				//loop thru other stars in vector
				for (int p = 0; p < starsArray.size(); p++)
				{
					//Don't use same star from first loop thru stars and don't use a star that is in a DESTROYED state
					if (p != i && starsArray[p].state != iStar::StarState::DESTROYED)
					{
						//Capture other star game object
						GameObject& obj_other_star = Play::GetGameObject(starsArray[p].starID);
						
						//if stars are colliding
						if (Play::IsColliding(obj_Star, obj_other_star))
						{
							//store 1st stars speed to switch with star it is colliding with
							float switchSpeed = starsArray[i].starSpeed;
							//1st star takes speed of other star
							starsArray[i].starSpeed = starsArray[p].starSpeed;
							//2nd star takes the speed from the 1st star
							starsArray[p].starSpeed = switchSpeed;
							//calculate angle 1st star hits 2nd star at
							starsArray[i].angle = atan2(obj_Star.pos.x - obj_other_star.pos.x, -(obj_Star.pos.y - obj_other_star.pos.y));
							//reset 1st star's rotation to 0
							starsArray[i].rotationSpeed = 0.0f;
							//set 1st star's velocity based on new speed and new angle
							starsArray[i].starVelocity = { starsArray[i].starSpeed * sin(starsArray[i].angle),  starsArray[i].starSpeed * -cos(starsArray[i].angle) };

							//calculate angle 2nd star hits 1st star at
							starsArray[p].angle = atan2(obj_other_star.pos.x - obj_Star.pos.x, -(obj_other_star.pos.y - obj_Star.pos.y));
							//reset 2nd star's rotation to 0
							starsArray[p].rotationSpeed = 0.0f;
							//set 2nd star's velocity based on new speed and new angle
							starsArray[p].starVelocity = { starsArray[p].starSpeed * sin(starsArray[p].angle),  starsArray[p].starSpeed * -cos(starsArray[p].angle) };
						}
					}
				//end loop of other stars
				}

				//if star game object is colliding with player game object handle movement and player health
				if (Play::IsColliding(obj_Star, obj_Player))
				{
						//switch statement based on player's state
						switch (plr1->state)
						{
						//if player is normal then register normal damage to player
						case Player::NORMAL:
							Play::PlayAudio("starHitNormal");
							//substract 25 health from player, if statement is so that player doesn't keep registering damage while star is moving away from player
							if (plr1->lastStarHit == starsArray[i].starID && plr1->spikeballHitClock < 0.1f){}
							else plr1->health -= 25;

							//so that player doesn't keep registering damage while star is moving away from player keep track of star.
							plr1->lastStarHit = starsArray[i].starID;
							//if health drops below 0
							if (plr1->health <= 0)
							{
								//set health to 0 so it can't into negatives
								plr1->health = 0;
								//change player state to DEAD
								plr1->state = Player::DEAD;
							}
							//reset star(spikeball) hit clock so player image will change to being hit
							plr1->spikeballHitClock = 0.0f;
							break;

						//if player is SHIELDED then register less damage to player
						case Player::SHIELDED:
							Play::PlayAudio("starHitShield");
							//substract 10 health from player, , if statement is so that player doesn't keep registering damage while star is moving away from player
							if (plr1->lastStarHit == starsArray[i].starID && plr1->spikeballHitClock < 0.1f) {}
							else plr1->health -= 10;

							//so that player doesn't keep registering damage while star is moving away from player keep track of star.
							plr1->lastStarHit = starsArray[i].starID;

							//if health drops below 0
							if (plr1->health <= 0)
							{
								//set health to 0 so it can't into negatives
								plr1->health = 0;
								//change player state to DEAD
								plr1->state = Player::DEAD;
							}
							//reset star(spikeball) hit clock so player image will change to being hit
							plr1->spikeballHitClock = 0.0f;
							break;

						//if player is CAT then player takes no damage from star and turns star into yarn ball
						case Player::CAT:
							Play::PlayAudio("yarn");
							//change star state to YARN
							starsArray[i].state = iStar::StarState::YARN;
							//Set star image to Yarn ball
							Play::SetSprite(obj_Star, "yarn", 0.0f);
							//reset star(spikeball) hit clock so player image will change to being hit
							plr1->spikeballHitClock = 0.0f;
							break;
						}

						//set star speed to a little faster then the player's speed so player can't move into star
						starsArray[i].starSpeed = plr1->spaces+1;
						//calculate angle star hits player at
						starsArray[i].angle = atan2(obj_Star.pos.x - obj_Player.pos.x, -(obj_Star.pos.y - obj_Player.pos.y));
						//reset star's rotation to 0
						starsArray[i].rotationSpeed = 0.0f;
						//set star's velocity based on new speed and new angle
						starsArray[i].starVelocity = { starsArray[i].starSpeed * sin(starsArray[i].angle),  starsArray[i].starSpeed * -cos(starsArray[i].angle) };
				}

				//switch statement based on star state
				switch (starsArray[i].state)
				{
				//if star state is NORMAL set image to normal star(spikeball) image
				case iStar::StarState::NORMAL:
					//set image to normal star image
					Play::SetSprite(obj_Star, "spikeball", 0.0f);
					//screen wrap star if star goes off screen
					StarScreenWrap(obj_Star);
					break;
				//if star state is YARN
				case iStar::StarState::YARN:
					//screen wrap star if star goes off screen
					StarScreenWrap(obj_Star);
					//loop thru all lasers that have been created
					for (int p = 0; p < lasers->lasersArray.size(); p++)
					{
						//capture laser game object
						GameObject& obj_Laser = Play::GetGameObject(lasers->lasersArray[p].laserID);
						//if star in YARN state collides with laser that isn't already in DESTROYED state
						if (GameObj::Collide(obj_Laser, obj_Star) && lasers->lasersArray[p].state != Lasers::iLaser::DESTROYED)
						{
							//change laser state to DESTROYED
							lasers->lasersArray[p].state = Lasers::iLaser::DESTROYED;
							//save the level that laser was destoryed at so it will be reactivated to NORMAL if player advances to next level
							lasers->lasersArray[p].levelDestroyed = game->game.level;
							//Add 10 to player score for destroying laser
							plr1->score += 10;
						}
					}
					break;

				//If star isn't set to a state do nothing(not possible)
				default:
					break;
				}
				break;
			//if game state is in any other state but play freeze stars
			default:
				//set star velocity and rotation speed to 0 so star freezes during alerts or paused game
				obj_Star.velocity = { 0,0 };
				starsArray[i].rotationSpeed = 0.0f;
				break;
			}
			//Update star game object with new settings
			Play::UpdateGameObject(obj_Star);
			//draw star game object with updates
			Play::DrawObjectRotated(obj_Star);
		}
		//if star is in a DESTROYED state
		else
		{
			//switch statement based on game state
			switch (game->game.state)
			{
			//IF game state is in PLAY keep track of where it is and reactivate back to NORMAL if player advances to next level from when star was DESTROYED
			case MainGame::PLAY:
				//if star is leaving screen but player is still on same level star was DESTROYED
				if (Play::IsLeavingDisplayArea(obj_Star) && starsArray[i].levelDestroyed == game->game.level)
				{
					//Just screen wrap star
					StarScreenWrap(obj_Star);
				}
				//if star is leaving screen and player has advanced a level that star was DESTROYED on
				else if (Play::IsLeavingDisplayArea(obj_Star) && starsArray[i].levelDestroyed < game->game.level)
				{
					//screen wrap star
					StarScreenWrap(obj_Star);
					//Change star state to NORMAL so it can go back in play
					starsArray[i].state = iStar::StarState::NORMAL;
				}
				//track star object movement even while DESTROYED because it will be changed to NORMAL on next level
				Play::UpdateGameObject(obj_Star);
				break;
			//If game state is not in PLAY do nothing and DESTROYED star will freeze in place
			default:
				//do nothing
				break;
			}
		}
	}
}

//Method for screen wrapping stars that are leaving screen, takes in star game object in arguments
void const Stars::StarScreenWrap(GameObject& star) const
{
	//If star game object y position is more than screen height set postion to top of screen
	if (star.pos.y > Screen::DISPLAY_HEIGHT) star.pos.y = 0;
	//If star game object y position is less than 0 set postion to bottom of screen
	else if (star.pos.y < 0) star.pos.y = Screen::DISPLAY_HEIGHT;
	//If star game object x position is more than screen width set postion to left side of screen
	if (star.pos.x > Screen::DISPLAY_WIDTH) star.pos.x = 0;
	//If star game object x position is less than 0 set postion to right side of screen
	else if (star.pos.x < 0) star.pos.x = Screen::DISPLAY_WIDTH;
}

