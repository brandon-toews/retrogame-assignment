#include "Splash.h"
#define PLAY_IMPLEMENTATION

//Method to create ASCII Splash screen words
void const Splash::CreateSplashWords()
{
	//loop thru default lines per word
	for (int i = 0; i < linesPerWord; i++)
	{
		//Add another element to splash word LASER vector
		splashWord_Laser.push_back(iLine());
		//Assign the position of each line added based on screen dimensions and increments on each successive line
		splashWord_Laser[i].linePos = { (Screen::DISPLAY_WIDTH * 0.1f), (Screen::DISPLAY_HEIGHT * 0.15f) + (i*15) };

		//Add another element to splash word MAN vector
		splashWord_Man.push_back(iLine());
		//Assign the position of each line added based on screen dimensions and increments on each successive line
		splashWord_Man[i].linePos = { (Screen::DISPLAY_WIDTH * 0.5f), (Screen::DISPLAY_HEIGHT * 0.15f) + (255 + (i * 15)) };
	}

	//Assign 1st line of splash word LASER
	splashWord_Laser[0].line = "LLLLLLLLLLL";
	//Assign 2nd line of splash word LASER
	splashWord_Laser[1].line = "L:::::::::L";
	//Assign 3rd line of splash word LASER
	splashWord_Laser[2].line = "L:::::::::L";
	//Assign 4th line of splash word LASER
	splashWord_Laser[3].line = "LL:::::::LL";
	//Assign 5th line of splash word LASER
	splashWord_Laser[4].line = "  L:::::L                 aaaaaaaaaaaaa      ssssssssss       eeeeeeeeeeee    rrrrr   rrrrrrrrr";
	//Assign 6th line of splash word LASER
	splashWord_Laser[5].line = "  L:::::L                 a::::::::::::a   ss::::::::::s    ee::::::::::::ee  r::::rrr:::::::::r";
	//Assign 7th line of splash word LASER
	splashWord_Laser[6].line = "  L:::::L                 aaaaaaaaa:::::ass:::::::::::::s  e::::::eeeee:::::eer:::::::::::::::::r";
	//Assign 8th line of splash word LASER
	splashWord_Laser[7].line = "  L:::::L                          a::::as::::::ssss:::::se::::::e     e:::::err::::::rrrrr::::::r";
	//Assign 9th line of splash word LASER
	splashWord_Laser[8].line = "  L:::::L                   aaaaaaa:::::a s:::::s  ssssss e:::::::eeeee::::::e r:::::r     r:::::r";
	//Assign 10th line of splash word LASER
	splashWord_Laser[9].line = "  L:::::L                 aa::::::::::::a   s::::::s      e:::::::::::::::::e  r:::::r     rrrrrrr";
	//Assign 11th line of splash word LASER
	splashWord_Laser[10].line = "  L:::::L                a::::aaaa::::::a      s::::::s   e::::::eeeeeeeeeee   r:::::r";
	//Assign 12th line of splash word LASER
	splashWord_Laser[11].line = "  L:::::L         LLLLLLa::::a    a:::::assssss   s:::::s e:::::::e            r:::::r";
	//Assign 13th line of splash word LASER
	splashWord_Laser[12].line = "LL:::::::LLLLLLLLL:::::La::::a    a:::::as:::::ssss::::::se::::::::e           r:::::r";
	//Assign 14th line of splash word LASER
	splashWord_Laser[13].line = "L::::::::::::::::::::::La:::::aaaa::::::as::::::::::::::s  e::::::::eeeeeeee   r:::::r";
	//Assign 15th line of splash word LASER
	splashWord_Laser[14].line = "L::::::::::::::::::::::L a::::::::::aa:::as:::::::::::ss    ee:::::::::::::e   r:::::r";
	//Assign 16th line of splash word LASER
	splashWord_Laser[15].line = "LLLLLLLLLLLLLLLLLLLLLLLL  aaaaaaaaaa  aaaa sssssssssss        eeeeeeeeeeeeee   rrrrrrr";

	//Assign 1st line of splash word MAN
	splashWord_Man[0].line = "MMMMMMMM               MMMMMMMM";
	//Assign 2nd line of splash word MAN
	splashWord_Man[1].line = "M:::::::M             M:::::::M";
	//Assign 3rd line of splash word MAN
	splashWord_Man[2].line = "M::::::::M           M::::::::M";
	//Assign 4th line of splash word MAN
	splashWord_Man[3].line = "M:::::::::M         M:::::::::M";
	//Assign 5th line of splash word MAN
	splashWord_Man[4].line = "M::::::::::M       M::::::::::M  aaaaaaaaaaaaa  nnnn  nnnnnnnn";
	//Assign 6th line of splash word MAN
	splashWord_Man[5].line = "M:::::::::::M     M:::::::::::M  a::::::::::::a n:::nn::::::::nn";
	//Assign 7th line of splash word MAN
	splashWord_Man[6].line = "M:::::::M::::M   M::::M:::::::M  aaaaaaaaa:::::an::::::::::::::nn";
	//Assign 8th line of splash word MAN
	splashWord_Man[7].line = "M::::::M M::::M M::::M M::::::M           a::::ann:::::::::::::::n";
	//Assign 9th line of splash word MAN
	splashWord_Man[8].line = "M::::::M  M::::M::::M  M::::::M    aaaaaaa:::::a  n:::::nnnn:::::n";
	//Assign 10th line of splash word MAN
	splashWord_Man[9].line = "M::::::M   M:::::::M   M::::::M  aa::::::::::::a  n::::n    n::::n";
	//Assign 11th line of splash word MAN
	splashWord_Man[10].line = "M::::::M    M:::::M    M::::::M a::::aaaa::::::a  n::::n    n::::n";
	//Assign 12th line of splash word MAN
	splashWord_Man[11].line = "M::::::M     MMMMM     M::::::Ma::::a    a:::::a  n::::n    n::::n";
	//Assign 13th line of splash word MAN
	splashWord_Man[12].line = "M::::::M               M::::::Ma::::a    a:::::a  n::::n    n::::n";
	//Assign 14th line of splash word MAN
	splashWord_Man[13].line = "M::::::M               M::::::Ma:::::aaaa::::::a  n::::n    n::::n";
	//Assign 15th line of splash word MAN
	splashWord_Man[14].line = "M::::::M               M::::::M a::::::::::aa:::a n::::n    n::::n";
	//Assign 16th line of splash word MAN
	splashWord_Man[15].line = "MMMMMMMM               MMMMMMMM  aaaaaaaaaa  aaaa nnnnnn    nnnnnn";
	
	//Loop thru each line in splash words
	for (int i = 0; i < linesPerWord; i++)
	{
		//loop thru each character in line for splash word MAN
		for (int p = 0; p < splashWord_Man[i].line.size(); p++)
		{
			//Add another element to lineCharacter vector for splash word MAN
			splashWord_Man[i].lineChars.push_back(iLine::iCharacters());
			//Assign the position of each character in line added based on screen dimensions and increments on each successive characters. each character gets random position on y-axis so that it staggers when each character falls
			splashWord_Man[i].lineChars[p].charPos = { splashWord_Man[i].linePos.x + (p * 7), -(rand() % 1000)};
			//Assigns random fall speed for each character in line
			splashWord_Man[i].lineChars[p].charSpeed = (rand() % 5) + 5;
		}

		//loop thru each character in line for splash word LASER
		for (int p = 0; p < splashWord_Laser[i].line.size(); p++)
		{
			//Add another element to lineCharacter vector for splash word LASER
			splashWord_Laser[i].lineChars.push_back(iLine::iCharacters());
			//Assign the position of each character in line added based on screen dimensions and increments on each successive characters. each character gets random position on y-axis so that it staggers when each character falls
			splashWord_Laser[i].lineChars[p].charPos = { splashWord_Laser[i].linePos.x + (p * 7), -(rand() % 1000) };
			//Assigns random fall speed for each character in line
			splashWord_Laser[i].lineChars[p].charSpeed = (rand() % 5) + 5;
		}
	}
}

//Method to display ASCII Splash screen words
void const Splash::DisplaySplashWords()
{
	//loop thru each line for splash word MAN
	for (int i = 0; i < linesPerWord; i++)
	{
		//loop thru each character in line for splash word MAN
		for (int p = 0; p < splashWord_Man[i].line.length(); p++)
		{
			//create char variable with last element initilised as nothing
			char letter[1] = { 0 };
			//first element is assigned specific character accessed in the loop of the line
			letter[0] = splashWord_Man[i].line[p];
			//Display character according to character position stored 
			Play::DrawDebugText({ splashWord_Man[i].lineChars[p].charPos  }, letter, wordColour, false);

			//switch statement based on whether bool arrived
			switch (splashWord_Man[i].lineChars[p].arrived)
			{
			//if character bool arrived is false keep moving character down screen
			case false:
				//if character y-axis position is less than line y-axis position stored minus 5 
				if (splashWord_Man[i].lineChars[p].charPos.y < splashWord_Man[i].linePos.y - 5)
				{
					//increment character position by stored character speed
					splashWord_Man[i].lineChars[p].charPos.y += splashWord_Man[i].lineChars[p].charSpeed;
				}
				//Once character gets close to end postion but not there yet
				else if (splashWord_Man[i].lineChars[p].charPos.y != splashWord_Man[i].linePos.y)
				{
					//Change character postion to final y-axis position
					splashWord_Man[i].lineChars[p].charPos.y = splashWord_Man[i].linePos.y;
					//change bool arrived to true so character is no longer moved
					splashWord_Man[i].lineChars[p].arrived = true;
				}
				break;
			//if character bool arrived is true stop moving character down screen
			case true:
					break;
			}
		}
	}

	//loop thru each character in line for splash word LASER
	for (int i = 0; i < linesPerWord; i++)
	{
		//loop thru each character in line for splash word LASER
		for (int p = 0; p < splashWord_Laser[i].line.length(); p++)
		{
			//create char variable with last element initilised as nothing
			char otherLetter[1] = { 0 };
			//first element is assigned specific character accessed in the loop of the line
			otherLetter[0] = splashWord_Laser[i].line[p];

			//Display character according to character position stored 
			Play::DrawDebugText({ splashWord_Laser[i].lineChars[p].charPos }, otherLetter, wordColour, false);

			//switch statement based on whether bool arrived
			switch (splashWord_Laser[i].lineChars[p].arrived)
			{
			//if character bool arrived is false keep moving character down screen
			case false:
				//if character y-axis position is less than line y-axis position stored minus 5 
				if (splashWord_Laser[i].lineChars[p].charPos.y < splashWord_Laser[i].linePos.y - 5)
				{
					//increment character position by stored character speed
					splashWord_Laser[i].lineChars[p].charPos.y += splashWord_Laser[i].lineChars[p].charSpeed;
				}
				//Once character gets close to end postion but not there yet
				else if (splashWord_Laser[i].lineChars[p].charPos.y != splashWord_Laser[i].linePos.y)
				{
					//Change character postion to final y-axis position
					splashWord_Laser[i].lineChars[p].charPos.y = splashWord_Laser[i].linePos.y;
					//change bool arrived to true so character is no longer moved
					splashWord_Laser[i].lineChars[p].arrived = true;
				}
				break;

			//if character bool arrived is true stop moving character down screen
			case true:
				break;
			}
		}
	}
}
