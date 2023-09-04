#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "MainGame.h"
#include<iostream>
#include <cstring>
using namespace std;

//Class for storing Splash screen ASCII art words and methods for creating and displaying splash screen words
class Splash
{
public:

	//Method to create ASCII Splash screen words
	void const CreateSplashWords();
	//Method to display ASCII Splash screen words
	void const DisplaySplashWords();

	//struct for storing each individual line of characters for each word
	struct iLine 
	{
		//Line string which is assigned in Create splash words method
		string line;
		//Line position which is assigned in Create splash words method
		Point2f linePos;
		
		//struct inside individual line struct that stores each characters position, speed, and whehter it has reached its final postion
		struct iCharacters
		{
			//character's start postition set on create method
			Point2f charPos;
			//character's movement speed set on create method
			int charSpeed;
			//bool to tell if character has made it to final position, default is false
			bool arrived = false;
		};
		//vector to store all instances of individual characters with their attributes 
		vector<iCharacters> lineChars;
	};
	//vectors to store all instances of individual lines with their attributes for both splash screen words 
	vector<iLine> splashWord_Laser;
	vector<iLine> splashWord_Man;

	//Default lines of characters per splash screen word
	int const linesPerWord = 16;
	//Default word colour
	Play::Colour wordColour = { 0.0f, 90.0f, 0.0f };
};

