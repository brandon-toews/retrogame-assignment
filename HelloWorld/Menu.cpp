#include "Menu.h"
#define PLAY_IMPLEMENTATION
using namespace std;

//Create menu method for taking in string arguments to initialize the options and add to menuOption vector
void const Menu::CreateMenu(string option1, string option2, string option3)
{
	//Create vector of strings to store arguments passed into method to then loop thru
	vector<string> options;
	//Add each argument to vector
	options.push_back(option1);
	options.push_back(option2);
	options.push_back(option3);

	//Loop thru options vector
	for (int i = 0; i < options.size(); i++)
	{
		//Add element to menuOptions vector
		menuOptionsArray.push_back(menuOption());
		//store option number for making menu choices later
		menuOptionsArray[i].optionNumb = i;
		//Store argument string as option label to be displayed in menu
		menuOptionsArray[i].optionLabel = options[i];
		//based on menu Dimensions and screen size set cell dimensions for option
		menuOptionsArray[i].topLeft = { ((Screen::DISPLAY_WIDTH - menuSize.width) / 2), ((Screen::DISPLAY_HEIGHT - menuSize.height) / 2) + ((menuSize.height/options.size())*(i)) };
		menuOptionsArray[i].bottomRight = { ((Screen::DISPLAY_WIDTH - menuSize.width) / 2) * 2, ((Screen::DISPLAY_HEIGHT - menuSize.height) / 2) + ((menuSize.height / options.size()) * (i + 1)) };
	}
}

//Create menu method for taking in string arguments to initialize the options and add to menuOption vector
void const Menu::CreateMenu(string option1, string option2, string option3, string option4, string option5)
{
	//Create vector of strings to store arguments passed into method to then loop thru
	vector<string> options;
	//Add each argument to vector
	options.push_back(option1);
	options.push_back(option2);
	options.push_back(option3);
	options.push_back(option4);
	options.push_back(option5);

	//Loop thru options vector
	for (int i = 0; i < options.size(); i++)
	{
		//Add element to menuOptions vector
		menuOptionsArray.push_back(menuOption());
		//store option number for making menu choices later
		menuOptionsArray[i].optionNumb = i;
		//Store argument string as option label to be displayed in menu
		menuOptionsArray[i].optionLabel = options[i];
		//based on menu Dimensions and screen size set cell dimensions for option
		menuOptionsArray[i].topLeft = { ((Screen::DISPLAY_WIDTH - menuSize.width) / 2), ((Screen::DISPLAY_HEIGHT - menuSize.height) / 2) + ((menuSize.height / options.size()) * (i)) };
		menuOptionsArray[i].bottomRight = { ((Screen::DISPLAY_WIDTH - menuSize.width) / 2) * 2, ((Screen::DISPLAY_HEIGHT - menuSize.height) / 2) + ((menuSize.height / options.size()) * (i + 1)) };
	}
}

//Create menu method for taking in string arguments to initialize the options and add to menuOption vector
void const Menu::CreateMenu(string option1, string option2, string option3, string option4, string option5, string option6, string option7, string option8, string option9, string option10, string option11)
{
	//Create vector of strings to store arguments passed into method to then loop thru
	vector<string> options;
	//Add each argument to vector
	options.push_back(option1);
	options.push_back(option2);
	options.push_back(option3);
	options.push_back(option4);
	options.push_back(option5);
	options.push_back(option6);
	options.push_back(option7);
	options.push_back(option8);
	options.push_back(option9);
	options.push_back(option10);
	options.push_back(option11);

	//Loop thru options vector
	for (int i = 0; i < options.size(); i++)
	{
		//Add element to menuOptions vector
		menuOptionsArray.push_back(menuOption());
		//store option number for making menu choices later
		menuOptionsArray[i].optionNumb = i;
		//Store argument string as option label to be displayed in menu
		menuOptionsArray[i].optionLabel = options[i];
		//if Menu height is set to over 400
		if (menuSize.height < 400.0f)
		{
			//based on menu Dimensions and screen size set cell dimensions for option
			menuOptionsArray[i].topLeft = { ((Screen::DISPLAY_WIDTH - menuSize.width) / 2), ((Screen::DISPLAY_HEIGHT - menuSize.height) / 2) + ((menuSize.height / options.size()) * (i)) };
			menuOptionsArray[i].bottomRight = { ((Screen::DISPLAY_WIDTH - menuSize.width) / 2) * 2, ((Screen::DISPLAY_HEIGHT - menuSize.height) / 2) + ((menuSize.height / options.size()) * (i + 1)) };
		}
		//if menu height is on default
		else
		{
			//based on menu Dimensions and screen size set cell dimensions for option
			menuOptionsArray[i].topLeft = { ((Screen::DISPLAY_WIDTH - menuSize.width) / 2), ((Screen::DISPLAY_HEIGHT - menuSize.height) / 2) + 40 + ((menuSize.height / options.size()) * (i)) };
			menuOptionsArray[i].bottomRight = { ((Screen::DISPLAY_WIDTH - menuSize.width) / 2) * 2, ((Screen::DISPLAY_HEIGHT - menuSize.height) / 2) + 40 + ((menuSize.height / options.size()) * (i + 1)) };
		}
	}
}

//Method for changed menu option states based on user actions
void const Menu::UpdateMenu()
{
	//loop thru all menu options
	for (int i = 0; i < menuOptionsArray.size(); i++)
	{
		//if menu option number equals the menuChoice the user has set change option state to HIGHLIGHTED
		if (menuChoice == menuOptionsArray[i].optionNumb) menuOptionsArray[i].state = Menu::menuOption::HIGHLIGHTED;
		//if menu option number doesn't equal the menuChoice change option state to NORMAL
		else menuOptionsArray[i].state = Menu::menuOption::NORMAL;
	}
}

//Method for showing user what level or difficulty has been selected in level and difficulty menus
void const Menu::UpdateSelected(MainGame* game)
{
	//loop thru all menu options
	for (int i = 0; i < menuOptionsArray.size(); i++)
	{
		//Switch statement based on menuType state
		switch (menuType)
		{
		//If menuType state is DIFF
		case Menu::MenuType::DIFF:
			//If game difficulty equals the menuOption number change bool selected to true
			if (game->game.difficulty == i)  menuOptionsArray[i].selected = true;
			//If not cnage bool selected to false
			else menuOptionsArray[i].selected = false;
			break;
		//If menuType state is LEVEL
		case Menu::MenuType::LEVEL:
			//If game level equals the menuOption number change bool selected to true
			if (game->game.level == i+1)  menuOptionsArray[i].selected = true;
			//If not cnage bool selected to false
			else menuOptionsArray[i].selected = false;
			break;
		}
		
	}
}

//Method for drawing menu
void const Menu::DrawMenu() const
{
	//if menu height is less than 400
	if (menuSize.height < 400.0f)
	{
		//Display menu title based on screen and menu height/width dimensions
		Play::DrawFontText("font132px", menuTitle, { ((Screen::DISPLAY_WIDTH - menuSize.width) / 2) + (menuSize.width / 2) + 33, ((Screen::DISPLAY_HEIGHT - menuSize.height) / 2) - 50 }, Play::CENTRE);
		//Display menu window based on screen and menu height/width dimensions
		Play::DrawRect({ (Screen::DISPLAY_WIDTH - menuSize.width) / 2,(Screen::DISPLAY_HEIGHT - menuSize.height) / 2 }, { ((Screen::DISPLAY_WIDTH - menuSize.width) / 2) + menuSize.width, ((Screen::DISPLAY_HEIGHT - menuSize.height) / 2) + menuSize.height }, borderColour, true);
	}
	//if menu height is on default
	else
	{
		//Display menu title based on screen and menu height/width dimensions
		Play::DrawFontText("font132px", menuTitle, { ((Screen::DISPLAY_WIDTH - menuSize.width) / 2) + (menuSize.width / 2) + 33, ((Screen::DISPLAY_HEIGHT - menuSize.height) / 2) - 5 }, Play::CENTRE);
		//Display menu window based on screen and menu height/width dimensions
		Play::DrawRect({ (Screen::DISPLAY_WIDTH - menuSize.width) / 2,((Screen::DISPLAY_HEIGHT - menuSize.height) / 2) + 40 }, { ((Screen::DISPLAY_WIDTH - menuSize.width) / 2) + menuSize.width, ((Screen::DISPLAY_HEIGHT - menuSize.height) / 2) + menuSize.height + 40 }, borderColour, true);
	}
	//loop thru all menu options
	for (int i = 0; i < menuOptionsArray.size(); i++)
	{
		//switch statement based on option state
		switch (menuOptionsArray[i].state)
		{
		//If option state is NORMAL
		case Menu::menuOption::NORMAL:
			//Display option cell with normal colour based on menu dimensions and border thickness
			Play::DrawRect({ menuOptionsArray[i].topLeft.x + borderThickness, menuOptionsArray[i].topLeft.y + borderThickness }, { menuOptionsArray[i].bottomRight.x - borderThickness, menuOptionsArray[i].bottomRight.y - borderThickness }, menuOptionsArray[i].colour, true);
			break;
		//If option state is HIGHLIGHTED
		case Menu::menuOption::HIGHLIGHTED:
			//Display option cell with highlighted colour based on menu dimensions and border thickness
			Play::DrawRect({ menuOptionsArray[i].topLeft.x + borderThickness, menuOptionsArray[i].topLeft.y + borderThickness }, { menuOptionsArray[i].bottomRight.x - borderThickness, menuOptionsArray[i].bottomRight.y - borderThickness }, menuOptionsArray[i].highlightColour, true);
			break;

		}
		//If option bool selected is true then display a spikeball image next to option lable so that the user knows what is currently selected
		if (menuOptionsArray[i].selected == true) Play::DrawSpriteRotated("spikeball", { ((menuOptionsArray[i].bottomRight.x - menuOptionsArray[i].topLeft.x) / 2) + menuOptionsArray[i].topLeft.x + 80, ((menuOptionsArray[i].bottomRight.y - menuOptionsArray[i].topLeft.y) / 2) + menuOptionsArray[i].topLeft.y }, 0, 0.0f, 0.75f);
		//Display option label in cell based on option dimentions
		Play::DrawFontText("font64px", menuOptionsArray[i].optionLabel, { ((menuOptionsArray[i].bottomRight.x - menuOptionsArray[i].topLeft.x) / 2) + menuOptionsArray[i].topLeft.x + 10, ((menuOptionsArray[i].bottomRight.y - menuOptionsArray[i].topLeft.y) / 2) + menuOptionsArray[i].topLeft.y }, Play::CENTRE);
	}
}

//Method for handling user controls on menu
void const Menu::UserMenuControls()
{
	//If up arrow is pressed
	if (Play::KeyPressed(VK_UP))
	{
		//Change menu choice by incrementing down but not past 0
		if (menuChoice > 0) menuChoice--;
	}
	//If down arrow is pressed
	else if (Play::KeyPressed(VK_DOWN))
	{
		//Change menu choice by incrementing up but not past the size of the menu option vector
		if (menuChoice < (menuOptionsArray.size()-1)) menuChoice++;
	}
}

//Method for announcing to player that they have moved onto new level
void const Menu::NewLevelAlert(MainGame* game) const
{
	//Display main window based on screen and menu dimensions
	Play::DrawRect({ (Screen::DISPLAY_WIDTH - alertMenuSize.width) / 2,(Screen::DISPLAY_HEIGHT - alertMenuSize.height) / 2 }, { ((Screen::DISPLAY_WIDTH - alertMenuSize.width) / 2) + alertMenuSize.width, ((Screen::DISPLAY_HEIGHT - alertMenuSize.height) / 2) + alertMenuSize.height }, borderColour, true);

	//Display cell coloured window based on screen and menu dimensions
	Play::DrawRect({ (Screen::DISPLAY_WIDTH - alertMenuSize.width) / 2 + borderThickness, (Screen::DISPLAY_HEIGHT - alertMenuSize.height) / 2 + borderThickness }, { ((Screen::DISPLAY_WIDTH - alertMenuSize.width) / 2) + alertMenuSize.width - borderThickness, ((Screen::DISPLAY_HEIGHT - alertMenuSize.height) / 2) + alertMenuSize.height - borderThickness }, { 0.0f, 50.0f, 0.0f }, true);

	//Create string taking in game level from MainGame instance
	string newLevel = to_string(game->game.level).c_str();
	newLevel = "Level " + newLevel;

	//Display string based on screen and menu dimensions
	Play::DrawFontText("font132px", newLevel, { ((Screen::DISPLAY_WIDTH - alertMenuSize.width) / 2) + (alertMenuSize.width/2)+35,  ((Screen::DISPLAY_HEIGHT - alertMenuSize.height) / 2) + (alertMenuSize.height / 2)+3 }, Play::CENTRE);
}

//Method to display game and player stats when game has ended due to losing
void const Menu::GameOverAlert(Player* plr, MainGame* game) const
{
	//Display menu title based on screen and menu height/width dimensions
	Play::DrawFontText("font132px", menuTitle, { ((Screen::DISPLAY_WIDTH - endGameMenuSize.width) / 2) + (endGameMenuSize.width / 2) + 33, ((Screen::DISPLAY_HEIGHT - endGameMenuSize.height) / 2) - 50 }, Play::CENTRE);
	//Display menu window based on screen and end game menu height/width dimensions
	Play::DrawRect({ (Screen::DISPLAY_WIDTH - endGameMenuSize.width) / 2,(Screen::DISPLAY_HEIGHT - endGameMenuSize.height) / 2 }, { ((Screen::DISPLAY_WIDTH - endGameMenuSize.width) / 2) + endGameMenuSize.width, ((Screen::DISPLAY_HEIGHT - endGameMenuSize.height) / 2) + endGameMenuSize.height }, borderColour, true);
	//Display cell coloured window based on screen and end game menumenu dimensions
	Play::DrawRect({ (Screen::DISPLAY_WIDTH - endGameMenuSize.width) / 2 + borderThickness, (Screen::DISPLAY_HEIGHT - endGameMenuSize.height) / 2 + borderThickness }, { ((Screen::DISPLAY_WIDTH - endGameMenuSize.width) / 2) + endGameMenuSize.width - borderThickness, ((Screen::DISPLAY_HEIGHT - endGameMenuSize.height) / 2) + endGameMenuSize.height - borderThickness }, { 0.0f, 50.0f, 0.0f }, true);

	//create difficulty string to display later
	string difficulty;

	//Switch statment based on game difficulty set in MainGame instance passed into method
	switch (game->game.difficulty)
	{
	//If difficulty is set to EASY
	case MainGame::Difficulty::EASY:
		//Set string to Easy
		difficulty = "Easy";
		break;

	//If difficulty is set to NORMAL
	case MainGame::Difficulty::NORMAL:
		//Set string to normal
		difficulty = "Normal";
		break;

	//If difficulty is set to HARD
	case MainGame::Difficulty::HARD:
		//Set string to Hard
		difficulty = "Hard";
		break;
	}
	//Display difficulty string based on screen and end game menumenu dimensions
	Play::DrawFontText("font132px", "You Lose - " + difficulty, { ((Screen::DISPLAY_WIDTH - endGameMenuSize.width) / 2) + (endGameMenuSize.width / 2) + 35,  ((Screen::DISPLAY_HEIGHT - endGameMenuSize.height) / 2) + (endGameMenuSize.height * 0.25f) }, Play::CENTRE);

	//Create string taking in game level from MainGame instance
	string gameLevel = to_string(game->game.level).c_str();
	gameLevel = "Level: " + gameLevel;

	//Display game level string based on screen and menu dimensions
	Play::DrawFontText("font132px", gameLevel, { ((Screen::DISPLAY_WIDTH - endGameMenuSize.width) / 2) + (endGameMenuSize.width / 2) + 35,  ((Screen::DISPLAY_HEIGHT - endGameMenuSize.height) / 2) + (endGameMenuSize.height * 0.5f) }, Play::CENTRE);

	//Create string taking in player score from player instance passed into method
	string plrScore = to_string(plr->score).c_str();
	plrScore = "Score: " + plrScore;

	//Display player score string based on screen and menu dimensions
	Play::DrawFontText("font132px", plrScore, { ((Screen::DISPLAY_WIDTH - endGameMenuSize.width) / 2) + (endGameMenuSize.width / 2) + 35,  ((Screen::DISPLAY_HEIGHT - endGameMenuSize.height) / 2) + (endGameMenuSize.height * 0.75f) }, Play::CENTRE);

	//Display instructions for player to start again by pressing enter
	Play::DrawFontText("font64px", "Press Enter to play again...", { Screen::DISPLAY_WIDTH / 2,  Screen::DISPLAY_HEIGHT * 0.8f }, Play::CENTRE);
}

//Method to display game and player stats when game has ended due to losing
void const Menu::WinGameAlert(Player* plr, MainGame* game) const
{
	//Display menu title based on screen and menu height/width dimensions
	Play::DrawFontText("font132px", menuTitle, {((Screen::DISPLAY_WIDTH - endGameMenuSize.width) / 2) + (endGameMenuSize.width / 2) + 33, ((Screen::DISPLAY_HEIGHT - endGameMenuSize.height) / 2) - 50}, Play::CENTRE);

	//Display menu window based on screen and end game menu height/width dimensions
	Play::DrawRect({ (Screen::DISPLAY_WIDTH - endGameMenuSize.width) / 2,(Screen::DISPLAY_HEIGHT - endGameMenuSize.height) / 2 }, { ((Screen::DISPLAY_WIDTH - endGameMenuSize.width) / 2) + endGameMenuSize.width, ((Screen::DISPLAY_HEIGHT - endGameMenuSize.height) / 2) + endGameMenuSize.height }, borderColour, true);

	//Display cell coloured window based on screen and end game menu height/width dimensions
	Play::DrawRect({ (Screen::DISPLAY_WIDTH - endGameMenuSize.width) / 2 + borderThickness, (Screen::DISPLAY_HEIGHT - endGameMenuSize.height) / 2 + borderThickness }, { ((Screen::DISPLAY_WIDTH - endGameMenuSize.width) / 2) + endGameMenuSize.width - borderThickness, ((Screen::DISPLAY_HEIGHT - endGameMenuSize.height) / 2) + endGameMenuSize.height - borderThickness }, { 0.0f, 50.0f, 0.0f }, true);

	//create difficulty string to display later
	string difficulty;

	//Switch statment based on game difficulty set in MainGame instance passed into method
	switch (game->game.difficulty)
	{
	//If difficulty is set to EASY
	case MainGame::Difficulty::EASY:
		//Set string to Easy
		difficulty = "Easy";
		break;
	//If difficulty is set to NORMAL
	case MainGame::Difficulty::NORMAL:
		//Set string to Normal
		difficulty = "Normal";
		break;
	//If difficulty is set to HARD
	case MainGame::Difficulty::HARD:
		//Set string to Hard
		difficulty = "Hard";
		break;
	}
	//Display difficulty string basedon screen and end game menumenu dimensions
	Play::DrawFontText("font132px", "You Win - " + difficulty, {((Screen::DISPLAY_WIDTH - endGameMenuSize.width) / 2) + (endGameMenuSize.width / 2) + 35,  ((Screen::DISPLAY_HEIGHT - endGameMenuSize.height) / 2) + (endGameMenuSize.height * 0.25f)}, Play::CENTRE);

	//Create string taking in player from player instance passed into method
	string plrHealth = to_string(plr->health).c_str();
	plrHealth = "Health: " + plrHealth + "%";

	//Display player score string based on screen and menu dimensions
	Play::DrawFontText("font132px", plrHealth, { ((Screen::DISPLAY_WIDTH - endGameMenuSize.width) / 2) + (endGameMenuSize.width / 2) + 35,  ((Screen::DISPLAY_HEIGHT - endGameMenuSize.height) / 2) + (endGameMenuSize.height * 0.5f)}, Play::CENTRE);

	//Create string taking in player score from player instance passed into method
	string plrScore = to_string(plr->score).c_str();
	plrScore = "Score: " + plrScore;

	//Display player score string based on screen and menu dimensions
	Play::DrawFontText("font132px", plrScore, { ((Screen::DISPLAY_WIDTH - endGameMenuSize.width) / 2) + (endGameMenuSize.width / 2) + 35,  ((Screen::DISPLAY_HEIGHT - endGameMenuSize.height) / 2) + (endGameMenuSize.height * 0.75f) }, Play::CENTRE);

	//Display instructions for player to start again by pressing enter
	Play::DrawFontText("font64px", "Press Enter to play again...", { Screen::DISPLAY_WIDTH / 2,  Screen::DISPLAY_HEIGHT * 0.8f }, Play::CENTRE);
}
