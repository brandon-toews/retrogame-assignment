#include "PowerUps.h"
#define PLAY_IMPLEMENTATION
using namespace std;

// Method for creating power ups
void const PowerUps::CreatePowerUps()
{
	//create shield power up object and store game object ID in ID variable
	shield.ID = Play::CreateGameObject(GameObj::TYPE_POWERUP, { (std::rand() % Screen::DISPLAY_WIDTH), yPos }, 25, "powerup_shield");
	//set shield realse clock ahead by 2.5 sec so that is staggers release from cat powerup
	shield.releaseClock = 2.5f;

	//create cat power up object and store game object ID in ID variable
	cat.ID = Play::CreateGameObject(GameObj::TYPE_POWERUP, { (std::rand() % Screen::DISPLAY_WIDTH), yPos }, 25, "powerup_cat");
}

//Method for moving powerups and handling player collisions, takes in time and player and maingame intances as arguments
void const PowerUps::MovePowerUps(float elapsedTime, Player* plr1, MainGame* game)
{
	//capture player and power up objects using their respective IDs
	GameObject& obj_Player = Play::GetGameObject(plr1->playerID);
	GameObject& obj_Shield = Play::GetGameObject(shield.ID);
	GameObject& obj_Cat = Play::GetGameObject(cat.ID);

	//Switch statement based on game state
	switch (game->game.state)
	{
	//If game state is PLAY
	case MainGame::PLAY:
		//increment both powerup release clocks with time
		shield.releaseClock += elapsedTime;
		cat.releaseClock += elapsedTime;

		//if shield object release clock is over 5 sec start moving power up down screen
		if (shield.releaseClock > 5) obj_Shield.velocity = { 0, shield.powerUpSpeed };
		//if shield object release clock is not over 5 sec don't release it
		else obj_Shield.velocity = { 0, 0 };

		//if cat object release clock is over 5 sec start moving power up down screen
		if (cat.releaseClock > 5) obj_Cat.velocity = { 0, cat.powerUpSpeed };
		//if cat object release clock is not over 5 sec don't release it
		else obj_Cat.velocity = { 0, 0 };

		//if shield power up object collides with player
		if (Play::IsColliding(obj_Shield, obj_Player))
		{
			Play::PlayAudio("powerUp");
			//Change player state to SHIELDED
			plr1->state = Player::PlayerState::SHIELDED;
			//Set player powerup clock to 0
			plr1->powerUpClock = 0.0f;
			//Set shield release clock to 0
			shield.releaseClock = 0.0f;
			//reset shield position to random spot on x-axis and default spot on y-axis
			obj_Shield.pos = { (std::rand() % Screen::DISPLAY_WIDTH), yPos };
		}
		//If shield power up is leaving screen
		else if (Play::IsLeavingDisplayArea(obj_Shield))
		{
			//Set shield release clock to 0
			shield.releaseClock = 0.0f;
			//reset shield position to random spot on x-axis and default spot on y-axis
			obj_Shield.pos = { (std::rand() % Screen::DISPLAY_WIDTH), yPos };
		}

		//if cat power up object collides with player
		if (Play::IsColliding(obj_Cat, obj_Player))
		{
			Play::PlayAudio("powerUp");
			//Change player state to CAT
			plr1->state = Player::PlayerState::CAT;
			//Set player powerup clock to 0
			plr1->powerUpClock = 0.0f;
			//Set cat release clock to 0
			cat.releaseClock = 0.0f;
			//reset cat position to random spot on x-axis and default spot on y-axis
			obj_Cat.pos = { (std::rand() % Screen::DISPLAY_WIDTH), yPos };
		}
		//If cat power up is leaving screen
		else if (Play::IsLeavingDisplayArea(obj_Cat))
		{
			//Set cat release clock to 0
			cat.releaseClock = 0.0f;
			//reset cat position to random spot on x-axis and default spot on y-axis
			obj_Cat.pos = { (std::rand() % Screen::DISPLAY_WIDTH), yPos };
		}
		break;
	//if game state is in PAUSE, NEWLEVEL or GAMEOVER freeze powerups
	default:
		obj_Shield.velocity = { 0, 0 };
		obj_Cat.velocity = { 0, 0 };
		break;
	}
	
	//Update shield and cat power ups with new settings and draw power up with updated settings
	Play::UpdateGameObject(obj_Shield);
	Play::DrawObject(obj_Shield);
	Play::UpdateGameObject(obj_Cat);
	Play::DrawObject(obj_Cat);
}