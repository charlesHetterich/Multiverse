#include "stdafx.h"
#include "Score.h"

CScore::CScore(CSDL_setup* csdl_setup)
{
	sdl_Setup = csdl_setup;
	maxIntegers = 10;
	scoreOrigin = (sdl_Setup->getScreenWidth / 2) - 50;
	while (currentInteger < maxIntegers)
	{
		integerImage[currentInteger] = new Csprites(sdl_Setup, "images/numbers.png", scoreOrigin, 100, 50, 50, 16, 18);
		currentInteger++;
	}
	currentInteger = 0;

	totalScoreIntigersAmount = 1;

}


CScore::~CScore()
{
	delete integerImage;
}

void CScore::setScore(int newScore)
{
	score = newScore;

	while (scoreUpTo < score)
	{
		integer[0]++;

		//sets each integerValue
		while (currentInteger < maxIntegers)
		{
			if (currentInteger < maxIntegers - 1)
			{
				if (integer[currentInteger] == 10) { integer[currentInteger] = 0; integer[currentInteger + 1]++; }
			}
			else if (integer[currentInteger] == 10) { integer[currentInteger] = 9;}
			if (integer[currentInteger] > 0) { totalScoreIntigersAmount = currentInteger + 1; }
			currentInteger++;
		}
		currentInteger = 0;

		//corresponds integer image with integer value
		while (currentInteger < maxIntegers)
		{
			integerImage[currentInteger]->setFrame(integer[currentInteger]);
			currentInteger++;
		}
		currentInteger = 0;

		scoreUpTo++;
	}
	scoreUpTo = 0;
	
	//figuring out width of whole score
	totalScoreWidth = totalScoreIntigersAmount * integerImage[0]->getW();
	//std::cout << totalScoreWidth << "    " << score <<"\n";

	//set positions of each integer
	while (currentInteger < totalScoreIntigersAmount)
	{
		integerImage[currentInteger]->setX((scoreOrigin + totalScoreWidth/2) - (integerImage[0]->getW()*currentInteger+1));
		currentInteger++;
	}
	currentInteger = 0;
}

int CScore::getScore()
{
	return score;
}

void CScore::displayScore()
{
	//display the score
	while (currentInteger < maxIntegers)
	{
		if (currentInteger < totalScoreIntigersAmount) { integerImage[currentInteger]->drawReg(0, 0); }
		integer[currentInteger] = 0;
		currentInteger++;
	}
	currentInteger = 0;
}

void CScore::resetScore()
{
	score = 0;
	totalScoreIntigersAmount = 1;
	totalScoreWidth = totalScoreIntigersAmount * integerImage[0]->getW();
	//set positions of each integer
	while (currentInteger < totalScoreIntigersAmount)
	{
		integerImage[currentInteger]->setX((scoreOrigin + totalScoreWidth / 2) - (integerImage[0]->getW()*currentInteger + 1));
		currentInteger++;
	}
	currentInteger = 0;
	while (currentInteger < maxIntegers)
	{
		integerImage[currentInteger]->setFrame(0);
		currentInteger++;
	}
	currentInteger = 0;
}