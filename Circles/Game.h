#include "stdafx.h"
#include "sprites.h"
#include "music.h"
#include "Mouse.h"
#include "planets.h"
#include "Score.h"
#include "SDL_setup.h"
#include "Player.h"
#include "SolarSystem.h"
#include "InfoObjects.h"
#include "Text.h"
#pragma once
class CGame
{
public:
	CGame();
	~CGame();
	void gameLoop();
	void saveGame();

	//different screens
	void homeScreen();
	void theGame();
	void loadScreen();

	//side functions
	void missions();

private:
	//game timer
	int gameSpeed;
	int gameTicks;

	//main music
	CMusic* gameMusic;

	/*keeps track of what screen is running
	0: home screen
	1: actual game
	2: loading screen*/
	int screenNumber;

	//screen transitions
	Csprites* screenChanger;

	//////////////////////////
	/////Main Menu Things/////
	//////////////////////////

	//text
	CText* text;
	CText* mainMenuText[5];

	//background
	CPlanet* mainMenuPlanets[5];

	//selector
	float selectedLoc[2]; //0: options 1: the grey indicator
	int selectedOption;
	bool selectorChanged;
	Csprites* mainMenuSelector[3];




	/////////////////////////
	/////The Game Things/////
	/////////////////////////

	//missions
	int missionNumber;

	//pause menu
	bool gamePaused;
	bool pausing;
	bool resuming;
	float selectedOptionPos;
	Csprites* pauseMenuCover;
	Csprites* pauseMenuSideBar;
	float sideBarPos;
	CText* pauseMenuOptions[5];
	Csprites* pauseMenuSelector;

	//informal objects
	CInfoObjects* informalObjects;

	//rocket
	CPlayer* player;

	//background
	Csprites* backgroud;

	//universe
	Csprites* universeBoundaries;
	long int scopeOfUniverse;
	double playerDistanceFromCenterOfUniverse;
	float playerAngleToCenterOfUniverse;

	//solar systems
	CSolarSystem* solarSystem[10000];
	int solarSystemsAmount;
	int currentSolarSystem;
	CPlanet* planet[1];
	int planetsAmount;
	int furthestSolarSystem;
	double furthestSolarSystemDistance;


	//////////////////////
	/////Other Things/////
	//////////////////////

	//mainImageController
	Csprites* mainScreenImageController;

	CSDL_setup* sdl_Setup;
	bool quit;
};

