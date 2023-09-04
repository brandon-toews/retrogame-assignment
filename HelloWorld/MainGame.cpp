#pragma once
#define PLAY_IMPLEMENTATION
#include "MainGame.h"

//Create pointers for instances of classes used
//Create instance of MainGame class for the game itself
MainGame* const mainGame = new MainGame();
//Create instance of Player class for the player
Player* const player1 = new Player();
//Create instance of Screen class for screen methods and settings
Screen* const screen = new Screen();
//Create instance of Stars class for stars(spikeballs)
Stars* const stars = new Stars();
//Create instance of Laser class for lasers
Lasers* const lasers = new Lasers();
//Create instance of PowerUps class for Powerups
PowerUps* const powerUps = new PowerUps();
//Create instances of Menu class for each menu window
Menu* const mainMenu = new Menu();
Menu* const settingsMenu = new Menu();
Menu* const diffMenu = new Menu();
Menu* const levelMenu = new Menu();
Menu* const pauseMenu = new Menu();
Menu* const alertMenu = new Menu();
//Create instance of Splash class for the splash screen
Splash* const splashScreen = new Splash();

// The entry point for a PlayBuffer program
void MainGameEntry(PLAY_IGNORE_COMMAND_LINE)
{
	//Initialize different menu windows with titles, labels, MenuType, and some window dimensions
	mainMenu->menuTitle = "Main Menu";
	mainMenu->CreateMenu("Play", "Settings", "Quit");
	settingsMenu->menuTitle = "Settings";
	settingsMenu->CreateMenu("Difficulty", "Level", "Back");
	settingsMenu->menuType = Menu::MenuType::SETTINGS;
	diffMenu->menuTitle = "Difficulty";
	diffMenu->CreateMenu("Easy", "Normal", "Hard", "Back", "Main Menu");
	diffMenu->menuType = Menu::MenuType::DIFF;
	levelMenu->menuSize.height = 600.0f;
	levelMenu->menuTitle = "Level";
	levelMenu->CreateMenu("Level 1", "Level 2", "Level 3", "Level 4", "Level 5", "Level 6", "Level 7", "Level 8", "Level 9", "Level 10", "Back");
	levelMenu->menuType = Menu::MenuType::LEVEL;
	pauseMenu->menuTitle = "Paused";
	pauseMenu->CreateMenu("Resume", "Restart", "Quit");
	pauseMenu->menuType = Menu::MenuType::PAUSED;
	alertMenu->menuTitle = "LaserMan";
	alertMenu->alertMenuSize.height = 125.0f;
	alertMenu->endGameMenuSize.width = 600.0f;
	//Create splash screen words out of rows of ASCII characters
	splashScreen->CreateSplashWords();
	//Create window for playing game in with screen dimensions stored in Screen class
	Play::CreateManager(Screen::DISPLAY_WIDTH, Screen::DISPLAY_HEIGHT, Screen::DISPLAY_SCALE);
	//Centre game object positions on centre of sprite and not top left corner of sprite
	Play::CentreAllSpriteOrigins();
	//Set background music
	Play::StartAudioLoop("FinalBoss");
	//Create the player game object through the instance on Player class
	player1->CreatePlayer();
	//Create the power up game objects through the instance on PowerUps class
	powerUps->CreatePowerUps();
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	//Clear screen with black background
	Play::ClearDrawingBuffer(Play::cBlack);
	//switch statement for handling actions taken at different game states
	switch (mainGame->game.state)
	{
	//If game state is SPLASH
	case MainGame::State::SPLASH:
		
		//Run method in Splash class from instance to play ASCII art animation
		splashScreen->DisplaySplashWords();

		//Draw 3 lasers on splash screen at 1.5 times normal size
		Play::DrawSpriteRotated("laser", { (Screen::DISPLAY_WIDTH * 0.75f), (Screen::DISPLAY_HEIGHT * 0.3f) }, 0, 0.0f, 1.5f);
		Play::DrawSpriteRotated("laser", { (Screen::DISPLAY_WIDTH * 0.8f), (Screen::DISPLAY_HEIGHT * 0.25f) }, 0, 0.0f, 1.5f);
		Play::DrawSpriteRotated("laser", { (Screen::DISPLAY_WIDTH * 0.85f), (Screen::DISPLAY_HEIGHT * 0.4f) }, 0, 0.0f, 1.5f);
		//Draw player image on splash screen at 3 times normal size
		Play::DrawSpriteRotated("player", { (Screen::DISPLAY_WIDTH * 0.25f), (Screen::DISPLAY_HEIGHT * 0.7f) }, 0, 0.0f, 3.0f);
		//If enter or space is pressed move on to STARTMENU game state 
		if (Play::KeyPressed(VK_RETURN) || Play::KeyPressed(VK_SPACE))
		{
			//Set game state to STARTMENU from MainGame instance
			mainGame->game.state = MainGame::State::STARTMENU;
		}
		break;

	//If game state is STARTMENU
	case MainGame::State::STARTMENU:
		//switch statement for handles which menu window to bring up based on game's  menu state
		switch (mainGame->game.whichMenu)
		{
		//If game menu state is MAIN
		case MainGame::MenuNav::MAIN:
			//Bring up main menu through Menu instance and handle menu based on user actions, update and draw menu according to user input
			mainMenu->UserMenuControls();
			mainMenu->UpdateMenu();
			mainMenu->DrawMenu();
			//If enter is pressed
			if (Play::KeyPressed(VK_RETURN))
			{
				//switch statement for handling what to do depending on which menu option is highighted when enter key is pressed
				switch (mainMenu->menuChoice)
				{
				//If 1st option is highlighted start game with default settings, start by going into NEWLEVEL state which announces what level player is on
				case 0:
					//Set game state to NEWLEVEL from MainGame instance
					mainGame->game.state = MainGame::State::NEWLEVEL;
					break;
				//If 2nd option is highlighted
				case 1:
					//Set game menu state to SETTINGS from MainGame instance which goes into settings menu
					mainGame->game.whichMenu = MainGame::MenuNav::SETTINGS;
					break;
				//If 3rd option is highlighted
				case 2:
					//Quit game
					return true;
					break;
				//If no option is highlighted do nothing(Can't actually highlight nothing)
				default:
					break;
				}
			}
			break;
		//If game menu state is SETTINGS
		case MainGame::MenuNav::SETTINGS:
			//Bring up settings menu through Menu instance and handle menu based on user actions, update and draw menu according to user input
			settingsMenu->UserMenuControls();
			settingsMenu->UpdateMenu();
			settingsMenu->DrawMenu();
			//If enter is pressed
			if (Play::KeyPressed(VK_RETURN))
			{
				//switch statement for handling what to do depending on which menu option is highighted when enter key is pressed
				switch (settingsMenu->menuChoice)
				{
				//If 1st option is highlighted
				case 0:
					//Set game menu state to DIFF from MainGame instance which goes into difficulty menu where user can set game difficulty
					mainGame->game.whichMenu = MainGame::MenuNav::DIFF;
					break;
				//If 2nd option is highlighted
				case 1:
					//Set game menu state to LEVEL from MainGame instance which goes into level menu where user can set which level to start at
					mainGame->game.whichMenu = MainGame::MenuNav::LEVEL;
					break;
				//If 3rd option is highlighted
				case 2:
					//Set game menu state to MAIN from MainGame instance which brings user back to main menu
					mainGame->game.whichMenu = MainGame::MenuNav::MAIN;
					break;
				//If no option is highlighted do nothing(Can't actually highlight nothing)
				default:
					break;
				}
			}
			break;
		//If game menu state is DIFF
		case MainGame::MenuNav::DIFF:
			//Bring up settings menu through Menu instance and handle menu based on user actions, update and draw menu according to user input.
			diffMenu->UserMenuControls();
			//Method used to display spikeball image on what difficulty the game is currently set at so the user knows what is selected
			diffMenu->UpdateSelected(mainGame);
			diffMenu->UpdateMenu();
			diffMenu->DrawMenu();
			//If enter is pressed
			if (Play::KeyPressed(VK_RETURN))
			{
				//switch statement for handling what to do depending on which menu option is highighted when enter key is pressed
				switch (diffMenu->menuChoice)
				{
				//If 1st option is highlighted
				case 0:
					//Change difficulty to EASY from MainGame instance 
					mainGame->game.difficulty = MainGame::Difficulty::EASY;
					break;
				//If 2nd option is highlighted
				case 1:
					//Change difficulty to NORMAL from MainGame instance
					mainGame->game.difficulty = MainGame::Difficulty::NORMAL;
					break;
				//If 3rd option is highlighted
				case 2:
					//Change difficulty to HARD from MainGame instance
					mainGame->game.difficulty = MainGame::Difficulty::HARD;
					break;
				//If 4th option is highlighted
				case 3:
					//Set game menu state to SETTINGS from MainGame instance which goes into settings menu
					mainGame->game.whichMenu = MainGame::MenuNav::SETTINGS;
					break;
				//If 5th option is highlighted
				case 4:
					//Set game menu state to MAIN from MainGame instance which brings user back to main menu
					mainGame->game.whichMenu = MainGame::MenuNav::MAIN;
					break;
				//If no option is highlighted do nothing(Can't actually highlight nothing)
				default:
					break;
				}
			}
			break;
		//If game menu state is LEVEL
		case MainGame::MenuNav::LEVEL:
			//Bring up settings menu through Menu instance and handle menu based on user actions, update and draw menu according to user input.
			levelMenu->UserMenuControls();
			//Method used to display spikeball image on what level the game is currently set at so the user knows what is selected
			levelMenu->UpdateSelected(mainGame);
			levelMenu->UpdateMenu();
			levelMenu->DrawMenu();
			//If enter is pressed
			if (Play::KeyPressed(VK_RETURN))
			{
				//switch statement for handling what to do depending on which menu option is highighted when enter key is pressed
				switch (levelMenu->menuChoice)
				{
				//If 1st option is highlighted
				case 0:
					//Change level to 1 from MainGame instance
					mainGame->game.level = 1;
					break;
				//If 2nd option is highlighted
				case 1:
					//Change level to 2 from MainGame instance
					mainGame->game.level = 2;
					break;
				//If 3rd option is highlighted
				case 2:
					//Change level to 3 from MainGame instance
					mainGame->game.level = 3;
					break;
				//If 4th option is highlighted
				case 3:
					//Change level to 4 from MainGame instance
					mainGame->game.level = 4;
					break;
				//If 5th option is highlighted
				case 4:
					//Change level to 5 from MainGame instance
					mainGame->game.level = 5;
					break;
				//If 6th option is highlighted
				case 5:
					//Change level to 6 from MainGame instance
					mainGame->game.level = 6;
					break;
				//If 7th option is highlighted
				case 6:
					//Change level to 7 from MainGame instance
					mainGame->game.level = 7;
					break;
				//If 8th option is highlighted
				case 7:
					//Change level to 8 from MainGame instance
					mainGame->game.level = 8;
					break;
				//If 9th option is highlighted
				case 8:
					//Change level to 9 from MainGame instance
					mainGame->game.level = 9;
					break;
				//If 10th option is highlighted
				case 9:
					//Change level to 10 from MainGame instance
					mainGame->game.level = 10;
					break;
				//If 11th option is highlighted
				case 10:
					//Set game menu state to SETTINGS from MainGame instance which goes into settings menu
					mainGame->game.whichMenu = MainGame::MenuNav::SETTINGS;
					break;
				//If no option is highlighted do nothing(Can't actually highlight nothing)
				default:
					break;
				}
			}
			break;
		}
		break;
	//If game state is PLAY
	case MainGame::State::PLAY:
		//Run Create and Move lasers methods from Lasers class instance
		//Create the lasers
		lasers->CreateLasers(elapsedTime);
		//Take in Player, Stars, MainGame instances as arguments. Move the lasers
		lasers->MoveLasers(player1, stars, mainGame);
		//Run Create and Move Stars methods from Stars class instance
		//Create the stars
		stars->CreateStars(elapsedTime);
		//Take in Player, Lasers, MainGame instances as arguments
		stars->MoveStars(player1, lasers, mainGame);
		//Run Move Player method from Player class instance, take in time and MainGame instance as arguments
		player1->MovePlayer(elapsedTime, mainGame);
		//Run MovePowerUps method from PowerUps class instance, take in time, MainGame & player instances as arguments
		powerUps->MovePowerUps(elapsedTime, player1, mainGame);
		//Run DisplayPlayerStats method from Screen class instance, take in player instance as argument
		screen->DisplayPlayerStats(player1);
		//Run UpdateLevel method from MainGame class instance, take in time, lasers & stars instance as arguments so they can be changed each level
		mainGame->UpdateLevel(elapsedTime/*, lasers, stars*/);
		//Run DisplayGameStats method from Screen class instance, take in MainGame instance as argument
		screen->DisplayGameStats(mainGame);
		//If enter or space is pressed set game state to PAUSED
		if (Play::KeyPressed(VK_RETURN) || Play::KeyPressed(VK_SPACE)) mainGame->game.state = MainGame::PAUSE;
		break;
	//If game state is NEWLEVEL
	case MainGame::State::NEWLEVEL:
		//Run Move lasers method from Lasers class instance, take in Player, Stars, MainGame instances as arguments. Method is written to freeze all lasers.
		lasers->MoveLasers(player1, stars, mainGame);
		//Run Move stars method from Stars class instance, take in Player, Lasers, MainGame instances as arguments. Method is written to freeze all stars.
		stars->MoveStars(player1, lasers, mainGame);
		//Run Move Player method from Player class instance, take in time and MainGame instance as arguments. Freezes player.
		player1->MovePlayer(elapsedTime, mainGame);
		//Run MovePowerUps method from PowerUps class instance, take in time, MainGame & player instances as arguments. Freezes powerups.
		powerUps->MovePowerUps(elapsedTime, player1, mainGame);
		//Run DisplayPlayerStats method from Screen class instance, take in player instance as argument
		screen->DisplayPlayerStats(player1);
		//Run DisplayGameStats method from Screen class instance, take in MainGame instance as argument
		screen->DisplayGameStats(mainGame);
		//Run NewLevelAlert method from Menu class instance, take in MainGame instance as argument. Displays level that player is moving on to.
		alertMenu->NewLevelAlert(mainGame);
		//If enter or space is pressed set game state to PLAY
		if (Play::KeyPressed(VK_RETURN) || Play::KeyPressed(VK_SPACE)) mainGame->game.state = MainGame::PLAY;
		break;
	//If game state is PAUSE
	case MainGame::State::PAUSE:
		//Run Move lasers method from Lasers class instance, take in Player, Stars, MainGame instances as arguments. Method is written to freeze all lasers.
		lasers->MoveLasers(player1, stars, mainGame);
		//Run Move stars method from Stars class instance, take in Player, Lasers, MainGame instances as arguments. Method is written to freeze all stars.
		stars->MoveStars(player1, lasers, mainGame);
		//Run Move Player method from Player class instance, take in time and MainGame instance as arguments. Freezes player.
		player1->MovePlayer(elapsedTime, mainGame);
		//Run MovePowerUps method from PowerUps class instance, take in time, MainGame & player instances as arguments. Freezes powerups.
		powerUps->MovePowerUps(elapsedTime, player1, mainGame);
		//Run DisplayPlayerStats method from Screen class instance, take in player instance as argument
		screen->DisplayPlayerStats(player1);
		//Run DisplayGameStats method from Screen class instance, take in MainGame instance as argument
		screen->DisplayGameStats(mainGame);
		//Bring up Pause menu through Menu instance and handle menu based on user actions, update and draw menu according to user input
		pauseMenu->UserMenuControls();
		pauseMenu->UpdateMenu();
		pauseMenu->DrawMenu();
		//If enter or space is pressed
		if (Play::KeyPressed(VK_RETURN) || Play::KeyPressed(VK_SPACE))
		{
			//switch statement for handling what to do depending on which menu option is highighted when enter key is pressed
			switch (pauseMenu->menuChoice)
			{
			//If 1st option is highlighted
			case 0:
				//Set game state to PLAY
				mainGame->game.state = MainGame::PLAY;
				break;
			//If 2nd option is highlighted
			case 1:
				//Restarts game
				mainGame->ResetGame(/*lasers, stars, player1, powerUps, mainMenu, settingsMenu, pauseMenu*/);
				break;
			//If 3rd option is highlighted
			case 2:
				//Quit game
				return true;
				break;
			//If no option is highlighted do nothing(Can't actually highlight nothing)
			default:
				break;
			}
		}
		break;
	//If game state is GAMEOVER
	case MainGame::State::GAMEOVER:
		//Run Move lasers method from Lasers class instance, take in Player, Stars, MainGame instances as arguments. Method is written to freeze all lasers.
		lasers->MoveLasers(player1, stars, mainGame);
		//Run Move stars method from Stars class instance, take in Player, Lasers, MainGame instances as arguments. Method is written to freeze all stars.
		stars->MoveStars(player1, lasers, mainGame);
		//Run Move Player method from Player class instance, take in time and MainGame instance as arguments. Freezes player.
		player1->MovePlayer(elapsedTime, mainGame);
		//Run MovePowerUps method from PowerUps class instance, take in time, MainGame & player instances as arguments. Freezes powerups.
		powerUps->MovePowerUps(elapsedTime, player1, mainGame);
		//Run DisplayPlayerStats method from Screen class instance, take in player instance as argument
		screen->DisplayPlayerStats(player1);
		//Run DisplayGameStats method from Screen class instance, take in MainGame instance as argument
		screen->DisplayGameStats(mainGame);
		//Run GameOverAlert method from Menu class instance, take in MainGame and player instances as arguments. Displays level that the player got to, what difficulty they were on, what there score was. Also tells them they lost.
		alertMenu->GameOverAlert(player1, mainGame);
		//If enter is pressed reset game
		if (Play::KeyPressed(VK_RETURN)) mainGame->ResetGame();
		break;
	//If game state is WIN
	case MainGame::State::WIN:
		//Run WinGameAlert method from Menu class instance, take in MainGame and player instances as arguments. What difficulty they were on, what there score and health were. Also tells them they won.
		alertMenu->WinGameAlert(player1, mainGame);
		//If enter or space is pressed reset game
		if (Play::KeyPressed(VK_RETURN)) mainGame->ResetGame();
		break;
	//If game state is nothing do nothing
	default:
		break;
	}

	//Copy contents of this frame to next frame
	Play::PresentDrawingBuffer();
	//When player presses Esc quits program
	return Play::KeyDown(VK_ESCAPE);
}


//Method for changing game settings based on difficulty setting and level
void const MainGame::UpdateLevel(float time)
{
	//increment game timer to keep track of when to advance level
	game.timer += time;

	//switch statement for handling what to do depending game level
	switch (game.level)
	{
	//If game level is set to level 1
	case 1:
		//switch statement for handling what to do depending game difficulty
		switch (game.difficulty)
		{
		//If game difficulty is set to EASY
		case MainGame::Difficulty::EASY:
			//Set laser release time so that they stagger across screen more evenly
			lasers->releaseTime = 0.5f;
			//Set number of lasers on screen at one time
			lasers->numOfLasers = 10;
			//Set laser speed for all lasers
			lasers->laserSpeed = 2.0f;
			//Set number of stars on screen at one time
			stars->numOfStars = 1;
			break;
		//If game difficulty is set to NORMAL
		case MainGame::Difficulty::NORMAL:
			//Set laser release time so that they stagger across screen more evenly
			lasers->releaseTime = 0.3f;
			//Set number of lasers on screen at one time
			lasers->numOfLasers = 30;
			//Set laser speed for all lasers
			lasers->laserSpeed = 3.0f;
			//Set number of stars on screen at one time
			stars->numOfStars = 3;
			break;
		//If game difficulty is set to HARD
		case MainGame::Difficulty::HARD:
			//Set laser release time so that they stagger across screen more evenly
			lasers->releaseTime = 0.1f;
			//Set number of lasers on screen at one time
			lasers->numOfLasers = 30;
			//Set laser speed for all lasers
			lasers->laserSpeed = 5.0f;
			//Set number of stars on screen at one time
			stars->numOfStars = 5;
			break;
		}
		break;
	//If game level is set to level 2
	case 2:
		//switch statement for handling what to do depending game difficulty
		switch (game.difficulty)
		{
		//If game difficulty is set to EASY
		case MainGame::Difficulty::EASY:
			//Set laser release time so that they stagger across screen more evenly
			lasers->releaseTime = 0.5f;
			//Set number of lasers on screen at one time
			lasers->numOfLasers = 13;
			//Set laser speed for all lasers
			lasers->laserSpeed = 2.5f;
			//Set number of stars on screen at one time
			stars->numOfStars = 2;
			break;
		//If game difficulty is set to NORMAL
		case MainGame::Difficulty::NORMAL:
			//Set laser release time so that they stagger across screen more evenly
			lasers->releaseTime = 0.3f;
			//Set number of lasers on screen at one time
			lasers->numOfLasers = 35;
			//Set laser speed for all lasers
			lasers->laserSpeed = 3.777f;
			//Set number of stars on screen at one time
			stars->numOfStars = 4;
			break;
		//If game difficulty is set to HARD
		case MainGame::Difficulty::HARD:
			//Set laser release time so that they stagger across screen more evenly
			lasers->releaseTime = 0.1f;
			//Set number of lasers on screen at one time
			lasers->numOfLasers = 40;
			//Set laser speed for all lasers
			lasers->laserSpeed = 6.0f;
			//Set number of stars on screen at one time
			stars->numOfStars = 6;
			break;
		}
		break;
	//If game level is set to level 3
	case 3:
		//switch statement for handling what to do depending game difficulty
		switch (game.difficulty)
		{
		//If game difficulty is set to EASY
		case MainGame::Difficulty::EASY:
			//Set laser release time so that they stagger across screen more evenly
			lasers->releaseTime = 0.5f;
			//Set number of lasers on screen at one time
			lasers->numOfLasers = 17;
			//Set laser speed for all lasers
			lasers->laserSpeed = 3.0f;
			//Set number of stars on screen at one time
			stars->numOfStars = 2;
			break;
		//If game difficulty is set to NORMAL
		case MainGame::Difficulty::NORMAL:
			//Set laser release time so that they stagger across screen more evenly
			lasers->releaseTime = 0.3f;
			//Set number of lasers on screen at one time
			lasers->numOfLasers = 40;
			//Set laser speed for all lasers
			lasers->laserSpeed = 4.555f;
			//Set number of stars on screen at one time
			stars->numOfStars = 4;
			break;
		//If game difficulty is set to HARD
		case MainGame::Difficulty::HARD:
			//Set laser release time so that they stagger across screen more evenly
			lasers->releaseTime = 0.1f;
			//Set number of lasers on screen at one time
			lasers->numOfLasers = 50;
			//Set laser speed for all lasers
			lasers->laserSpeed = 7.0f;
			//Set number of stars on screen at one time
			stars->numOfStars = 7;
			break;
		}
		break;
	//If game level is set to level 4
	case 4:
		//switch statement for handling what to do depending game difficulty
		switch (game.difficulty)
		{
		//If game difficulty is set to EASY
		case MainGame::Difficulty::EASY:
			//Set laser release time so that they stagger across screen more evenly
			lasers->releaseTime = 0.5f;
			//Set number of lasers on screen at one time
			lasers->numOfLasers = 20;
			//Set laser speed for all lasers
			lasers->laserSpeed = 3.5f;
			//Set number of stars on screen at one time
			stars->numOfStars = 3;
			break;
		//If game difficulty is set to NORMAL
		case MainGame::Difficulty::NORMAL:
			//Set laser release time so that they stagger across screen more evenly
			lasers->releaseTime = 0.3f;
			//Set number of lasers on screen at one time
			lasers->numOfLasers = 45;
			//Set laser speed for all lasers
			lasers->laserSpeed = 5.333f;
			//Set number of stars on screen at one time
			stars->numOfStars = 4;
			break;
		//If game difficulty is set to HARD
		case MainGame::Difficulty::HARD:
			//Set laser release time so that they stagger across screen more evenly
			lasers->releaseTime = 0.1f;
			//Set number of lasers on screen at one time
			lasers->numOfLasers = 60;
			//Set laser speed for all lasers
			lasers->laserSpeed = 8;
			//Set number of stars on screen at one time
			stars->numOfStars = 8;
			break;
		}
		break;
	//If game level is set to level 5
	case 5:
		//switch statement for handling what to do depending game difficulty
		switch (game.difficulty)
		{
		//If game difficulty is set to EASY
		case MainGame::Difficulty::EASY:
			//Set laser release time so that they stagger across screen more evenly
			lasers->releaseTime = 0.5f;
			//Set number of lasers on screen at one time
			lasers->numOfLasers = 23;
			//Set laser speed for all lasers
			lasers->laserSpeed = 4.0f;
			//Set number of stars on screen at one time
			stars->numOfStars = 3;
			break;
		//If game difficulty is set to NORMAL
		case MainGame::Difficulty::NORMAL:
			//Set laser release time so that they stagger across screen more evenly
			lasers->releaseTime = 0.3f;
			//Set number of lasers on screen at one time
			lasers->numOfLasers = 50;
			//Set laser speed for all lasers
			lasers->laserSpeed = 6.111f;
			//Set number of stars on screen at one time
			stars->numOfStars = 5;
			break;
		//If game difficulty is set to HARD
		case MainGame::Difficulty::HARD:
			//Set laser release time so that they stagger across screen more evenly
			lasers->releaseTime = 0.1f;
			//Set number of lasers on screen at one time
			lasers->numOfLasers = 70;
			//Set laser speed for all lasers
			lasers->laserSpeed = 9.0f;
			//Set number of stars on screen at one time
			stars->numOfStars = 9;
			break;
		}
		break;
	//If game level is set to level 6
	case 6:
		//switch statement for handling what to do depending game difficulty
		switch (game.difficulty)
		{
		//If game difficulty is set to EASY
		case MainGame::Difficulty::EASY:
			//Set laser release time so that they stagger across screen more evenly
			lasers->releaseTime = 0.5f;
			//Set number of lasers on screen at one time
			lasers->numOfLasers = 27;
			//Set laser speed for all lasers
			lasers->laserSpeed = 4.5f;
			//Set number of stars on screen at one time
			stars->numOfStars = 4;
			break;
		//If game difficulty is set to NORMAL
		case MainGame::Difficulty::NORMAL:
			//Set laser release time so that they stagger across screen more evenly
			lasers->releaseTime = 0.3f;
			//Set number of lasers on screen at one time
			lasers->numOfLasers = 55;
			//Set laser speed for all lasers
			lasers->laserSpeed = 6.888f;
			//Set number of stars on screen at one time
			stars->numOfStars = 6;
			break;
		//If game difficulty is set to HARD
		case MainGame::Difficulty::HARD:
			//Set laser release time so that they stagger across screen more evenly
			lasers->releaseTime = 0.1f;
			//Set number of lasers on screen at one time
			lasers->numOfLasers = 80;
			//Set laser speed for all lasers
			lasers->laserSpeed = 10.0f;
			//Set number of stars on screen at one time
			stars->numOfStars = 10;
			break;
		}
		break;
	//If game level is set to level 7
	case 7:
		//switch statement for handling what to do depending game difficulty
		switch (game.difficulty)
		{
		//If game difficulty is set to EASY
		case MainGame::Difficulty::EASY:
			//Set laser release time so that they stagger across screen more evenly
			lasers->releaseTime = 0.3f;
			//Set number of lasers on screen at one time
			lasers->numOfLasers = 30;
			//Set laser speed for all lasers
			lasers->laserSpeed = 5.0f;
			//Set number of stars on screen at one time
			stars->numOfStars = 4;
			break;
		//If game difficulty is set to NORMAL
		case MainGame::Difficulty::NORMAL:
			//Set laser release time so that they stagger across screen more evenly
			lasers->releaseTime = 0.3f;
			//Set number of lasers on screen at one time
			lasers->numOfLasers = 60;
			//Set laser speed for all lasers
			lasers->laserSpeed = 7.666f;
			//Set number of stars on screen at one time
			stars->numOfStars = 7;
			break;
		//If game difficulty is set to HARD
		case MainGame::Difficulty::HARD:
			//Set laser release time so that they stagger across screen more evenly
			lasers->releaseTime = 0.1f;
			//Set number of lasers on screen at one time
			lasers->numOfLasers = 90;
			//Set laser speed for all lasers
			lasers->laserSpeed = 11.0f;
			//Set number of stars on screen at one time
			stars->numOfStars = 11;
			break;
		}
		break;
	//If game level is set to level 8
	case 8:
		//switch statement for handling what to do depending game difficulty
		switch (game.difficulty)
		{
		//If game difficulty is set to EASY
		case MainGame::Difficulty::EASY:
			//Set laser release time so that they stagger across screen more evenly
			lasers->releaseTime = 0.3f;
			//Set number of lasers on screen at one time
			lasers->numOfLasers = 33;
			//Set laser speed for all lasers
			lasers->laserSpeed = 5.5f;
			//Set number of stars on screen at one time
			stars->numOfStars = 5;
			break;
		//If game difficulty is set to NORMAL
		case MainGame::Difficulty::NORMAL:
			//Set laser release time so that they stagger across screen more evenly
			lasers->releaseTime = 0.3f;
			//Set number of lasers on screen at one time
			lasers->numOfLasers = 65;
			//Set laser speed for all lasers
			lasers->laserSpeed = 8.444f;
			//Set number of stars on screen at one time
			stars->numOfStars = 8;
			break;
		//If game difficulty is set to HARD
		case MainGame::Difficulty::HARD:
			//Set laser release time so that they stagger across screen more evenly
			lasers->releaseTime = 0.1f;
			//Set number of lasers on screen at one time
			lasers->numOfLasers = 100;
			//Set laser speed for all lasers
			lasers->laserSpeed = 12.0f;
			//Set number of stars on screen at one time
			stars->numOfStars = 12;
			break;
		}
		break;
	//If game level is set to level 9
	case 9:
		//switch statement for handling what to do depending game difficulty
		switch (game.difficulty)
		{
		//If game difficulty is set to EASY
		case MainGame::Difficulty::EASY:
			//Set laser release time so that they stagger across screen more evenly
			lasers->releaseTime = 0.3f;
			//Set number of lasers on screen at one time
			lasers->numOfLasers = 37;
			//Set laser speed for all lasers
			lasers->laserSpeed = 6.0f;
			//Set number of stars on screen at one time
			stars->numOfStars = 6;
			break;
		//If game difficulty is set to NORMAL
		case MainGame::Difficulty::NORMAL:
			//Set laser release time so that they stagger across screen more evenly
			lasers->releaseTime = 0.3f;
			//Set number of lasers on screen at one time
			lasers->numOfLasers = 70;
			//Set laser speed for all lasers
			lasers->laserSpeed = 9.333f;
			//Set number of stars on screen at one time
			stars->numOfStars = 9;
			break;
		//If game difficulty is set to HARD
		case MainGame::Difficulty::HARD:
			//Set laser release time so that they stagger across screen more evenly
			lasers->releaseTime = 0.1f;
			//Set number of lasers on screen at one time
			lasers->numOfLasers = 110;
			//Set laser speed for all lasers
			lasers->laserSpeed = 13.0f;
			//Set number of stars on screen at one time
			stars->numOfStars = 13;
			break;
		}
		break;
	//If game level is set to level 10
	case 10:
		//switch statement for handling what to do depending game difficulty
		switch (game.difficulty)
		{
		//If game difficulty is set to EASY
		case MainGame::Difficulty::EASY:
			//Set laser release time so that they stagger across screen more evenly
			lasers->releaseTime = 0.3f;
			//Set number of lasers on screen at one time
			lasers->numOfLasers = 40;
			//Set laser speed for all lasers
			lasers->laserSpeed = 6.5f;
			//Set number of stars on screen at one time
			stars->numOfStars = 7;
			break;
		//If game difficulty is set to NORMAL
		case MainGame::Difficulty::NORMAL:
			//Set laser release time so that they stagger across screen more evenly
			lasers->releaseTime = 0.3f;
			//Set number of lasers on screen at one time
			lasers->numOfLasers = 75;
			//Set laser speed for all lasers
			lasers->laserSpeed = 10.0f;
			//Set number of stars on screen at one time
			stars->numOfStars = 10;
			break;
		//If game difficulty is set to HARD
		case MainGame::Difficulty::HARD:
			//Set laser release time so that they stagger across screen more evenly
			lasers->releaseTime = 0.1f;
			//Set number of lasers on screen at one time
			lasers->numOfLasers = 120;
			//Set laser speed for all lasers
			lasers->laserSpeed = 14.0f;
			//Set number of stars on screen at one time
			stars->numOfStars = 14;
			break;
		}
		break;
	//If game level is set to nothing do nothing
	default:
		break;
	}
	//If game timer is over how long level should last and it is the 10th level
	if (game.timer > levelTime && game.level == 10)
	{
		//Set game state to WIN
		game.state = MainGame::WIN;
	}
	//If game timer is over how long level should last
	else if (game.timer > levelTime)
	{
		//increase game level
		game.level++;
		//Set game timer back to 0
		game.timer = 0;
		//Set game state to NEWLEVEL so that the new level can be announced to player
		game.state = MainGame::NEWLEVEL;
	}
}

//Method for resetting game when player wants to restart
void const MainGame::ResetGame()
{
	//Loop through all laser objects and destroy them
	for (int i = 0; i < lasers->lasersArray.size(); i++)
	{
		Play::DestroyGameObject(lasers->lasersArray[i].laserID);
	}
	//Clear laserArray vector
	lasers->lasersArray.clear();

	//Loop through all star objects and destroy them
	for (int i = 0; i < stars->starsArray.size(); i++)
	{
		Play::DestroyGameObject(stars->starsArray[i].starID);
	}
	//Clear starArray vector
	stars->starsArray.clear();
	
	//Set player settings back to default
	player1->health = 100;
	player1->score = 0;
	player1->state = Player::NORMAL;
	player1->powerUpClock = 0.0f;
	player1->laserHitClock = 0.5f;
	player1->spikeballHitClock = 0.5f;
	GameObject& obj_Player = Play::GetGameObjectByType(GameObj::TYPE_PLAYER);
	obj_Player.pos = { Screen::DISPLAY_WIDTH / 2 , Screen::DISPLAY_HEIGHT * 0.75f };

	//Set shield power up release clock back to default 
	powerUps->shield.releaseClock = 0.0f;
	//Reset shield power up postion
	GameObject& obj_Shield = Play::GetGameObject(powerUps->shield.ID);
	obj_Shield.pos = { (std::rand() % Screen::DISPLAY_WIDTH), powerUps->yPos };

	//Set cat power up release clock back to default 
	powerUps->cat.releaseClock = 0.0f;
	//Reset cat power up postion
	GameObject& obj_Cat = Play::GetGameObject(powerUps->cat.ID);
	obj_Cat.pos = { (std::rand() % Screen::DISPLAY_WIDTH), powerUps->yPos };

	//Reset menu options
	mainMenu->menuChoice = 0;
	settingsMenu->menuChoice = 0;
	pauseMenu->menuChoice = 0;

	//Reset game options to defaults
	mainGame->game.timer = 0;
	mainGame->game.level = 1;
	mainGame->game.state = MainGame::State::STARTMENU;
	mainGame->game.whichMenu = MainGame::MenuNav::MAIN;
	//mainGame->releaseClock = 0.0f;
}

// Gets called once when the player quits the game 
int MainGameExit( void )
{
	//Delete all class instances as program is ending
	delete mainGame;
	delete player1;
	delete screen;
	delete stars;
	delete lasers;
	delete powerUps;
	delete mainMenu;
	delete settingsMenu;
	delete diffMenu;
	delete levelMenu;
	delete pauseMenu;
	delete alertMenu;
	delete splashScreen;

	//Delete game window
	Play::DestroyManager();
	//Exit
	return PLAY_OK;
}
