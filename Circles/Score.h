#pragma once
#include "SDL_setup.h"
#include "sprites.h"

class CScore
{
public:
	CScore(CSDL_setup* csdl_setup);
	~CScore();
	void setScore(int newScore);
	int getScore();
	void displayScore();
	void resetScore();

private:

	int score;

	//for displaying score
	int scoreOrigin;
	int totalScoreWidth;
	int totalScoreIntigersAmount;
	int scoreUpTo;
	int maxIntegers;
	int currentInteger;
	Csprites* integerImage[10];
	int integer[10];
	
	CSDL_setup* sdl_Setup;
};

