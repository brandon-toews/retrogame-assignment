#include "Player.h"
#define PLAY_IMPLEMENTATION

//Method for creating player game object
void const Player::CreatePlayer()
{
	//Create player game object and store sprite ID in playerID
	playerID = Play::CreateGameObject(GameObj::TYPE_PLAYER, { Screen::DISPLAY_WIDTH / 2 , Screen::DISPLAY_HEIGHT * 0.75f }, 25, "player");
}

//Method for moving player game object, takes in time and MainGame instance for arguments
void const Player::MovePlayer(float elapsedTime, MainGame* game)
{
	//Capture player game object
	GameObject& obj_Player = Play::GetGameObject(playerID);

	//if player's health drops to 0 or below change player state to DEAD
	if (health <= 0) state = DEAD;

	//Switch statement based on player state
	switch (state)
	{
	//If player state is NORMAL
	case NORMAL:
		//If player hasn't been hit by either laser or star recently set sprite image to normal player image
		if (laserHitClock > 0.2f && spikeballHitClock > 0.2f) Play::SetSprite(obj_Player, "player", 0.0f);
		//If player has been hit by either laser or star recently set sprite image to player hit image
		else Play::SetSprite(obj_Player, "player_hit", 0.0f);

		//increment both hit clocks by time
		laserHitClock += elapsedTime;
		spikeballHitClock += elapsedTime;
		break;
	//If player state is SHIELDED
	case SHIELDED:
		//Switch statement based on game state
		switch (game->game.state)
		{
		//If game state is in PLAY
		case MainGame::PLAY:
			//If player's powerup clock is still only in the first 10 seconds and player hasn't been hit by a laser or star recently set player shield animation to slow speed
			if (powerUpClock < 10 && laserHitClock > 0.1f && spikeballHitClock > 0.2f) Play::SetSprite(obj_Player, "player_shield", 0.25f);
			//If player's powerup clock is past 10 sec but less than 15 seconds and player hasn't been hit by a laser or star recently set player shield animation to a little faster
			else if (powerUpClock > 10 && powerUpClock < 15 && laserHitClock > 0.1f && spikeballHitClock > 0.2f) Play::SetSprite(obj_Player, "player_shield", 0.5f);
			//If player's powerup clock is past 15 sec but less than 20 seconds and player hasn't been hit by a laser or star recently set player shield animation to fastest animation speed to indicate to player that powerup is about to run out
			else if (powerUpClock > 15 && powerUpClock < 20 && laserHitClock > 0.1f && spikeballHitClock > 0.2f) Play::SetSprite(obj_Player, "player_shield", 0.8f);
			//If player's powerup clock is past 20 sec player state back to NORMAL
			else if (powerUpClock > 20) state = NORMAL;
			//If player has been hit by laser recently change player image to shield laser hit
			else if (laserHitClock < 0.1f) Play::SetSprite(obj_Player, "player_shield_laserHit", 0.0f);
			//if the other conditions haven't been met then player has been hit by star recently change player image to shield spike(star) hit 
			else Play::SetSprite(obj_Player, "player_shield_spikeHit", 0.0f);
			//increment clocks with time
			powerUpClock += elapsedTime;
			laserHitClock += elapsedTime;
			spikeballHitClock += elapsedTime;
			break;
		//If game state is anything but PLAY then set player image to standard player shield image
		default:
			Play::SetSprite(obj_Player, "player_shield", 0.0f);
				break;
		}
		break;
	//If player state is CAT
	case CAT:
		//Switch statement based on game state
		switch (game->game.state)
		{
		//If game state is in PLAY
		case MainGame::PLAY:
			//If player's powerup clock is still only in the first 10 seconds and player hasn't been hit by a laser or star recently set player cat animation to slow speed
			if (powerUpClock < 10 && laserHitClock > 0.2f && spikeballHitClock > 0.2f) Play::SetSprite(obj_Player, "player_cat", 0.15f);
			//If player's powerup clock is past 10 sec but less than 15 seconds and player hasn't been hit by a laser or star recently set player shield animation to a little faster
			else if (powerUpClock > 10 && powerUpClock < 15 && laserHitClock > 0.2f && spikeballHitClock > 0.2f) Play::SetSprite(obj_Player, "player_cat", 0.3f);
			//If player's powerup clock is past 15 sec but less than 20 seconds and player hasn't been hit by a laser or star recently set player shield animation to fastest animation speed to indicate to player that powerup is about to run out
			else if (powerUpClock > 15 && powerUpClock < 20 && laserHitClock > 0.2f && spikeballHitClock > 0.2f) Play::SetSprite(obj_Player, "player_cat", 0.5f);
			//If player's powerup clock is past 20 sec player state back to NORMAL
			else if (powerUpClock > 20) state = NORMAL;
			//If player has been hit by laser recently change player image to shield laser hit
			else if (laserHitClock < 0.2f) Play::SetSprite(obj_Player, "player_cat_laserHit", 0.0f);
			//if the other conditions haven't been met then player has been hit by star recently change player image to shield spike(star) hit 
			else Play::SetSprite(obj_Player, "player_cat_spikeHit", 0.0f);
			//increment clocks with time
			powerUpClock += elapsedTime;
			laserHitClock += elapsedTime;
			spikeballHitClock += elapsedTime;
			break;
		//If game state is anything but PLAY then set player image to standard player cat image
		default:
			Play::SetSprite(obj_Player, "player_cat", 0.0f);
			break;
		}
		break;
	//If player state is DEAD
	case DEAD:
		//Change player image to dead player image
		Play::SetSprite(obj_Player, "player_dead", 0.0f);
		//Set game state to GAMEOVER
		game->game.state = MainGame::GAMEOVER;
		break;

	//If player state isn't set to anything then do nothing
	default:
		break;
	}

	//if user presses up arrow and game state is set to PLAY, move player up according to player spaces
	if (Play::KeyDown(VK_UP) && game->game.state == MainGame::PLAY) obj_Player.velocity = { 0, -spaces };
	//if user presses down arrow and game state is set to PLAY, move player down according to player spaces
	else if (Play::KeyDown(VK_DOWN) && game->game.state == MainGame::PLAY) obj_Player.velocity = { 0, spaces };
	//if user presses right arrow and game state is set to PLAY, move player right according to player spaces
	else if (Play::KeyDown(VK_RIGHT) && game->game.state == MainGame::PLAY) obj_Player.velocity = { spaces, 0 };
	//if user presses left arrow and game state is set to PLAY, move player left according to player spaces
	else if (Play::KeyDown(VK_LEFT) && game->game.state == MainGame::PLAY) obj_Player.velocity = { -spaces, 0 };
	//if user presses no arrow keys
	else obj_Player.velocity = { 0, 0 };

	//Update player game objects new settings
	Play::UpdateGameObject(obj_Player);
	//if player is leaving screen set player game object position to old position
	if (Play::IsLeavingDisplayArea(obj_Player, Play::ALL, 1)) obj_Player.pos = obj_Player.oldPos;
	//Display player object with updated settings
	Play::DrawObject(obj_Player);
}