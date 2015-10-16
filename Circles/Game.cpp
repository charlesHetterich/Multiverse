#include "stdafx.h"
#include "Game.h"

CGame::CGame()
{
	//////////////////////////
	/////Important Things/////
	//////////////////////////

	quit = false;
	sdl_Setup = new CSDL_setup(&quit, 1600, 900);
	srand(time(NULL));

	//music
	gameMusic = new CMusic();

	//time
	gameSpeed = 12;
	gameTicks = SDL_GetTicks();

	//screen transitions
	screenChanger = new Csprites(sdl_Setup, "images/blackdot.png", 0, 0, sdl_Setup->getScreenWidth, sdl_Setup->getScreenHeight, 1, 1);
	SDL_SetTextureColorMod(screenChanger->getTexture(), 0, 0, 0);
	screenChanger->setAplpha(0);

	//////////////////////////
	/////Main Menu Things/////
	//////////////////////////

	//text
	text = new CText(sdl_Setup);
	for (int x = 0; x < 5; x++) { mainMenuText[x] = new CText(sdl_Setup); }

	//background
	mainMenuPlanets[0] = new CPlanet(NULL, 0, sdl_Setup, NULL, sdl_Setup->getScreenWidth/2 + 100, sdl_Setup->getScreenHeight/2, 100, NULL, NULL, NULL, true, "images/white_circle_small.png", 172, 158, 124);
	mainMenuPlanets[1] = new CPlanet(NULL, 1, sdl_Setup, mainMenuPlanets[0], NULL, NULL, 50, NULL, 130, 0.2, false, "images/white_circle_small.png", 184, 218, 232);
	mainMenuPlanets[2] = new CPlanet(NULL, 1, sdl_Setup, mainMenuPlanets[0], NULL, NULL, 20, NULL, 200, 0.1, false, "images/white_circle_small.png", 200, 200, 200);
	mainMenuPlanets[3] = new CPlanet(NULL, 1, sdl_Setup, mainMenuPlanets[0], NULL, NULL, 70, NULL, 280, 0.3, false, "images/white_circle_small.png", 220, 206, 167);
	mainMenuPlanets[4] = new CPlanet(NULL, 1, sdl_Setup, mainMenuPlanets[0], NULL, NULL, 100, NULL, 450, 0.1, false, "images/white_circle_small.png", 148, 180, 193);

	//selector
	selectedLoc[0] = 500; selectedLoc[1] = 500;
	for (int x = 0; x < 3; x++) { mainMenuSelector[x] = new Csprites(sdl_Setup, "images/mainmenuselector.png", 90, 500 + x * 50, 400, 50, 1, 1); mainMenuSelector[x]->setAplpha(250); }


	/////////////////////////
	/////The Game Things/////
	/////////////////////////

	//screen image controller
	mainScreenImageController = new Csprites(sdl_Setup, "", NULL, NULL, NULL, NULL, NULL, NULL);

	//informal objects
	informalObjects = new CInfoObjects(sdl_Setup);

	//background
	backgroud = new Csprites(sdl_Setup, "images/whitedot.png", 0, 0, sdl_Setup->getScreenWidth, sdl_Setup->getScreenHeight, 1, 1);

	//player
	std::ifstream load("data/world");
	player = new CPlayer(sdl_Setup);
	if (load)
	{
		int offset;
		load >> offset;
		player->player->setX(offset);
		load >> offset;
		player->player->setY(offset);
		load.close();
	}

	/////////////////////////////////
	/////Pause Menu For The Game/////
	/////////////////////////////////
	pauseMenuCover = new Csprites(sdl_Setup, "images/blackdot.png", 0, 0, sdl_Setup->getScreenWidth, sdl_Setup->getScreenHeight, 1, 1);
	SDL_SetTextureColorMod(pauseMenuCover->getTexture(), 200, 200, 200);
	pauseMenuSideBar = new Csprites(sdl_Setup, "images/whitedot.png", 0, 0, 400, sdl_Setup->getScreenHeight, 1, 1);
	sideBarPos = -400;
	SDL_SetTextureColorMod(pauseMenuSideBar->getTexture(), 100, 100, 100);
	for (int x = 0; x < 5; x++) { pauseMenuOptions[x] = new CText(sdl_Setup); }
	pauseMenuSelector = new Csprites(sdl_Setup, "images/blackdot.png", 0, 400, 400, 50, 1, 1);
}

CGame::~CGame()
{
	delete sdl_Setup;
	delete planet;
	delete solarSystem;
	delete player;
	delete gameMusic;
	delete informalObjects;
	delete text;
}

void CGame::saveGame()
{
	std::ofstream save("data/world");

	save << player->player->getX() << " " << player->player->getY();

	save.close();
}

void CGame::gameLoop()
{
	gameMusic->playMusic(0);
	while (!quit && sdl_Setup->mainEvent->type != SDL_QUIT)
	{
		if (gameTicks + gameSpeed < SDL_GetTicks())
		{
			sdl_Setup->begin();

			//different screens running
			if (screenNumber == 0) { homeScreen(); }
			else if (screenNumber == 1) { theGame(); }
			else if (screenNumber == 2) { loadScreen(); }

			//screentransitions
			if (screenChanger->getAlpha() > 0) { screenChanger->setAplpha(screenChanger->getAlpha() - 1);}
			if (screenChanger->getAlpha() < 0) { screenChanger->setAplpha(0); }
			screenChanger->drawStatic();

			sdl_Setup->end();

			gameTicks = SDL_GetTicks();
		}
	}
}

void CGame::homeScreen()
{
	/////////////////////////
	/////Selector Things/////
	/////////////////////////

	//scrolling through selections
	if (SDL_JoystickGetAxis(player->getController(), 1) > 20000 && !selectorChanged) { selectedOption ++; selectorChanged = true; }
	else if (SDL_JoystickGetAxis(player->getController(), 1) < -20000 && !selectorChanged) { selectedOption--; selectorChanged = true; }
	else if (abs(SDL_JoystickGetAxis(player->getController(), 1)) < 20000) { selectorChanged = false; }
	if (selectedOption > 4) { selectedOption = 4; }
	else if (selectedOption < 0) { selectedOption = 0; }
	selectedLoc[0] += (500 - (selectedOption*25) - selectedLoc[0])/10;
	selectedLoc[1] -= (selectedLoc[1] - 500 - (selectedOption * 25)) / 10;

	//selecting
	if (SDL_JoystickGetButton(player->getController(), 10))
	{
		if (selectedOption == 1) { screenNumber = 2; }
		if (selectedOption == 4) { quit = true; }
	}

	////////////////////////
	/////Draw Main Menu/////
	////////////////////////

	for (int x = 0; x < 5; x++)
	{
		mainMenuPlanets[x]->rotate();
		mainMenuPlanets[x]->drawBackground();
	}

	mainMenuSelector[0]->setY(selectedLoc[1]);
	mainMenuSelector[0]->drawStatic();

	text->write("font/trench.otf", 200, "Multiverse", 100, 100, NULL, NULL, NULL);
	mainMenuText[0]->write("font/trench.otf", 50, "Resume", 100, selectedLoc[0], NULL, NULL, NULL);
	mainMenuText[1]->write("font/trench.otf", 50, "New Game", 100, selectedLoc[0] + 50, NULL, NULL, NULL);
	mainMenuText[2]->write("font/trench.otf", 50, "Credits", 100, selectedLoc[0] + 100, NULL, NULL, NULL);
	mainMenuText[3]->write("font/trench.otf", 50, "Settings", 100, selectedLoc[0] + 150, NULL, NULL, NULL);
	mainMenuText[4]->write("font/trench.otf", 50, "Quit", 100, selectedLoc[0] + 200, NULL, NULL, NULL);
}

void CGame::theGame()
{
	if (!gamePaused)
	{
		//all the solar system stuff besides drawing
		for (currentSolarSystem = 0; currentSolarSystem < solarSystemsAmount; currentSolarSystem++)
		{
			solarSystem[currentSolarSystem]->movePlanets();
		}
		for (currentSolarSystem = 0; currentSolarSystem < solarSystemsAmount; currentSolarSystem++)
		{
			solarSystem[currentSolarSystem]->updatePlayerStats(player);
		}
		for (currentSolarSystem = 0; currentSolarSystem < solarSystemsAmount; currentSolarSystem++)
		{
			solarSystem[currentSolarSystem]->planetCollision(player);
		}
		for (currentSolarSystem = 0; currentSolarSystem < solarSystemsAmount; currentSolarSystem++)
		{
			solarSystem[currentSolarSystem]->PlanetGravity(player);
		}
		for (currentSolarSystem = 0; currentSolarSystem < solarSystemsAmount; currentSolarSystem++)
		{
			solarSystem[currentSolarSystem]->playerMoveOnPlanet(player);
		}


		//update players stats to the universe
		playerDistanceFromCenterOfUniverse = sqrt(((float)(player->player->getX() + player->player->getW() / 2) * (float)(player->player->getX() + player->player->getW() / 2)) + ((float)(player->player->getY() + player->player->getH() / 2) * (float)(player->player->getY() + player->player->getH() / 2)));
		playerAngleToCenterOfUniverse = acos((player->player->getX() + player->player->getW() / 2) / playerDistanceFromCenterOfUniverse);
		if (player->player->getY() + player->player->getH() > 0) { playerAngleToCenterOfUniverse = -playerAngleToCenterOfUniverse + 2 * M_PI; }
		//universe holding player inside of the universe
		if (playerDistanceFromCenterOfUniverse > scopeOfUniverse)
		{
			player->playerVelocityX -= pow(playerDistanceFromCenterOfUniverse - scopeOfUniverse, 0.4) * cos(playerAngleToCenterOfUniverse);
			player->playerVelocityY += pow(playerDistanceFromCenterOfUniverse - scopeOfUniverse, 0.4) * sin(playerAngleToCenterOfUniverse);
		}


		player->controlPlayer();
		player->movePlayer();

		//set the focus of the screen
		mainScreenImageController->setFocusX(player->player->getX() + player->player->getW() / 2);
		mainScreenImageController->setFocusY(player->player->getY() + player->player->getH() / 2);
		mainScreenImageController->setZoom(mainScreenImageController->getZoom() + mainScreenImageController->getZoomSpeed());
		mainScreenImageController->zeroOutZoomSpeed();

		//set the screen reach
		mainScreenImageController->setSightReach(mainScreenImageController->getSightReachX() + ((-SDL_JoystickGetAxis(player->getController(), 2) / 40) - (mainScreenImageController->getSightReachX())) / 20, mainScreenImageController->getSightReachY() + ((-SDL_JoystickGetAxis(player->getController(), 3) / 40) - (mainScreenImageController->getSightReachY())) / 20);

		//check if game is paused
		if (SDL_JoystickGetButton(player->getController(), 4)) { gamePaused = true; selectedOption = 0; selectedOptionPos = 0;}
	}

	/////////////////////////////////
	///////DRAWING EVERYTHING////////
	/////////////////////////////////

	//background
	backgroud->drawStatic();
	universeBoundaries->drawReg(0, 0);
	//all the planets
	for (currentSolarSystem = 0; currentSolarSystem < solarSystemsAmount; currentSolarSystem++)
	{
		solarSystem[currentSolarSystem]->drawPlanets();
	}
	//the player
	player->showPlayer();
	//miniMap
	informalObjects->drawMap();
	for (currentSolarSystem = 0; currentSolarSystem < solarSystemsAmount; currentSolarSystem++)
	{
		informalObjects->mapObject(solarSystem[currentSolarSystem]->getCentralX(), solarSystem[currentSolarSystem]->getCentralY(), 0, 0, 0);
	}
	informalObjects->mapObject(player->player->getX() + player->player->getW(), player->player->getY() + player->player->getH(), 255, 100, 100);

	/////////////////////////
	////////All Text/////////
	/////////////////////////


	/////////////////////////////////
	////////Pause Menu Stuff/////////
	/////////////////////////////////
	if (gamePaused)
	{
		

	
		if (!pausing && !resuming)
		{
			//unpausing with start button
			if (SDL_JoystickGetButton(player->getController(), 4)) { resuming = true; }

			//scrolling through selections
			if (SDL_JoystickGetAxis(player->getController(), 1) > 20000 && !selectorChanged) { selectedOption++; selectorChanged = true; }
			else if (SDL_JoystickGetAxis(player->getController(), 1) < -20000 && !selectorChanged) { selectedOption--; selectorChanged = true; }
			else if (abs(SDL_JoystickGetAxis(player->getController(), 1)) < 20000) { selectorChanged = false; }
			if (selectedOption > 4) { selectedOption = 4; }
			else if (selectedOption < 0) { selectedOption = 0; }
			selectedOptionPos += ((selectedOption * 25) - selectedOptionPos) / 10;
			
			//selecting
			if (SDL_JoystickGetButton(player->getController(), 10))
			{
				if (selectedOption == 0) { resuming = true; }
				if (selectedOption == 4) { screenNumber = 0; selectedOption = 0; selectedLoc[0] = 500; selectedLoc[1] = 500; }
			}
		}

		//moving over pause Menu
		if (!resuming) { sideBarPos += ( 0 - pauseMenuSideBar->getX()) / 10; }
		else { sideBarPos += (-450 - pauseMenuSideBar->getX()) / 10; }
		pauseMenuCover->setAplpha((400 + sideBarPos) / 2);
		pauseMenuCover->drawStatic();
		pauseMenuSideBar->setX(sideBarPos);
		pauseMenuSideBar->drawStatic();
		if (pauseMenuSideBar->getX() < -10) { pausing = true; }
		else { pausing = false; }
		if (resuming && pauseMenuSideBar->getX() < -390) { gamePaused = false; resuming = false; }

		//draw selector
		pauseMenuSelector->setX(sideBarPos);
		pauseMenuSelector->setY(400 + selectedOptionPos);
		pauseMenuSelector->drawStatic();

		//draw options
		pauseMenuOptions[0]->write("font/trench.otf", 50, "Resume", sideBarPos + 20, 400 - selectedOptionPos, NULL, NULL, NULL);
		pauseMenuOptions[1]->write("font/trench.otf", 50, "Volume", sideBarPos + 20, 450 - selectedOptionPos, NULL, NULL, NULL);
		pauseMenuOptions[2]->write("font/trench.otf", 50, "Resume", sideBarPos + 20, 500 - selectedOptionPos, NULL, NULL, NULL);
		pauseMenuOptions[3]->write("font/trench.otf", 50, "Resume", sideBarPos + 20, 550 - selectedOptionPos, NULL, NULL, NULL);
		pauseMenuOptions[4]->write("font/trench.otf", 50, "Exit", sideBarPos + 20, 600 - selectedOptionPos, NULL, NULL, NULL);


	}
}

void CGame::loadScreen()
{
	//text->write("font/regular.ttf", 100, "Loading Universe", 100, 100, NULL, NULL, NULL);
	//solar systems
	solarSystemsAmount = 100;
	for (currentSolarSystem = 0; currentSolarSystem < solarSystemsAmount; currentSolarSystem++)
	{
		std::cout << currentSolarSystem << "\n";
		solarSystem[currentSolarSystem] = new CSolarSystem(currentSolarSystem, sdl_Setup, rand() % 12 + 4);
		bool solarSystemCollision = true;

		double placementAngle;
		double placementDistance;
		while (solarSystemCollision == true)
		{
			solarSystemCollision = false;
			placementAngle = (rand() % 200 * M_PI) / 100;
			placementDistance = (rand() * 100);
			solarSystem[currentSolarSystem]->placeSolarSystem(placementDistance*cos(placementAngle), placementDistance*sin(placementAngle));
			double distanceBetweenSolarSystems;
			for (int x = currentSolarSystem - 1; x >= 0 && solarSystemCollision == false; x--)
			{
				distanceBetweenSolarSystems = sqrt(((float)(solarSystem[currentSolarSystem]->getCentralX() - solarSystem[x]->getCentralX()) * (float)(solarSystem[currentSolarSystem]->getCentralX() - solarSystem[x]->getCentralX())) + ((float)(solarSystem[currentSolarSystem]->getCentralY() - solarSystem[x]->getCentralY()) * (float)(solarSystem[currentSolarSystem]->getCentralY() - solarSystem[x]->getCentralY())));
				if (distanceBetweenSolarSystems < solarSystem[currentSolarSystem]->getSolarSystemRadius() + solarSystem[x]->getSolarSystemRadius()) { solarSystemCollision = true; }
			}
		}
		if (placementDistance > furthestSolarSystemDistance) { furthestSolarSystem = currentSolarSystem; furthestSolarSystemDistance = placementDistance; }
	}

	scopeOfUniverse = furthestSolarSystemDistance + solarSystem[furthestSolarSystem]->getSolarSystemRadius() + 1000;
	universeBoundaries = new Csprites(sdl_Setup, "images/white_circle.png", -scopeOfUniverse, -scopeOfUniverse, scopeOfUniverse * 2, scopeOfUniverse * 2, 1000, 1000);
	SDL_SetTextureColorMod(universeBoundaries->getTexture(), 0, 0, 0);

	informalObjects->setMapScope(scopeOfUniverse);

	screenNumber = 1;

	screenChanger->setAplpha(255);

	//set all game starting values
	gamePaused = false;
	sideBarPos = -400;
}