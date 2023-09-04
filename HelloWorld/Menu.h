#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "MainGame.h"
using namespace std;

//Objects created from MainGame class are used in Menu class
class MainGame;

//Menu Class is used for everything having to do with menus
class Menu
{
public:

	//Overloaded CreateMenu method for creating three types of menus used in game
	void const CreateMenu(string option1, string option2, string option3);
	void const CreateMenu(string option1, string option2, string option3, string option4, string option5);
	void const CreateMenu(string option1, string option2, string option3, string option4, string option5, string option6, string option7, string option8, string option9, string option10, string option11);
	//Method for updating menu option highlighted
	void const UpdateMenu();
	//Method for showing player what level or difficulty game is set at
	void const UpdateSelected(MainGame* game);
	//Method for drawing menu
	void const DrawMenu() const;
	//Method for handling user controls
	void const UserMenuControls();
	//Methods for alert windows that just announce things to user
	void const NewLevelAlert(MainGame* game) const;
	void const GameOverAlert(Player* plr, MainGame* game) const;
	void const WinGameAlert(Player* plr, MainGame* game) const;

	//Each instance of class has...
	//menu title
	string menuTitle;
	//border Colour of menu
	Play::Colour borderColour = Play::cWhite;
	//Menu dimensions for normal menu
	Point2f menuSize = { 426.6f, 360.0f };
	//Menu dimensions for new level alert
	Point2f alertMenuSize = { 426.6f, 360.0f };
	//Menu Dimensions for win or lose alert windows
	Point2f endGameMenuSize = { 426.6f, 360.0f };
	//Border thickness
	int borderThickness = 5;
	//Default menu choice is the 1st option
	int menuChoice = 0;

	//enum for menu type
	enum MenuType
	{
		MAIN,
		SETTINGS,
		DIFF,
		LEVEL,
		PAUSED
	};
	//Default menu type is MAIN for main menu
	MenuType menuType = MAIN;

	//struct for creating individual options with different attributes
	struct menuOption
	{
		//enum for option state, either normal or highlighted
		enum optionState
		{
			NORMAL = 0,
			HIGHLIGHTED
		};
		//Default option state is NORMAL
		optionState state = NORMAL;

		//option number so we can keep track of what option is highlighted
		int optionNumb = NULL;
		//Option Label to be displayed
		string optionLabel;
		//Bool for options where the player need to be shown what value the setting is at
		bool selected = false;

		//Cell dimensions for option
		Point2f topLeft = { 0,0 };
		Point2f bottomRight = { 0,0 };
		//Default colour for when option is in NORMAL state
		Play::Colour colour = { 0.0f, 50.0f, 0.0f };
		//Colour for when option is in HIGHLIGHTED state
		Play::Colour highlightColour = { 50.0f, 0.0f, 0.0f };
	};
	//Vector of menuOption structs that hold all the information for each option created in menu
	vector<menuOption> menuOptionsArray;
};

