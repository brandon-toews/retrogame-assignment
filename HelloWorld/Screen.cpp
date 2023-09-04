#include "Screen.h"
#define PLAY_IMPLEMENTATION

//Method for displaying player stats that takes in Player class instance in argument
void const Screen::DisplayPlayerStats(Player* plr1) const
{
	//Create player health string to display players current health
	string player1Health = to_string(plr1->health).c_str();
	player1Health = "Health: " + player1Health + "%";

	//Display player health string according to screen dimensions
	Play::DrawFontText("font64px", player1Health, {Screen::DISPLAY_WIDTH - 165, Screen::DISPLAY_HEIGHT / 30}, Play::LEFT);

	//Create player score string to display players current score
	string player1Score = to_string(plr1->score).c_str();
	player1Score = "Score: " + player1Score;

	//Display player score string according to screen dimensions
	Play::DrawFontText("font64px", player1Score, { Screen::DISPLAY_WIDTH - 165, Screen::DISPLAY_HEIGHT / 10 }, Play::LEFT);
}

//Method for displaying game stats that takes in MainGame class instance in argument
void const Screen::DisplayGameStats(MainGame* game) const
{
	//Create game timer string to display game's time on the current level
	string gameTime = to_string(int(round(game->game.timer))).c_str();
	gameTime = "Time: " + gameTime;

	//Display game timer string according to screen dimensions
	Play::DrawFontText("font64px", gameTime, { 15, Screen::DISPLAY_HEIGHT / 30 }, Play::LEFT);

	//Create game level string to display game's current level
	string gameLevel = to_string(game->game.level).c_str();
	gameLevel = "Level: " + gameLevel;

	//Display game level string according to screen dimensions
	Play::DrawFontText("font64px", gameLevel, { 15, Screen::DISPLAY_HEIGHT / 10 }, Play::LEFT);
}

