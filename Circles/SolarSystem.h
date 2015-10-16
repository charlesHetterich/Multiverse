#pragma once
#include "SDL_setup.h"
#include "planets.h"
#include "Player.h"
class CSolarSystem
{
public:
	CSolarSystem(int SolarSystemNumber, CSDL_setup* csdl_Setup, int PlanetsAmount);
	~CSolarSystem();
	int getSolarSystemRadius();
	CPlanet* getPlanet(int planetNumber);
	void placeSolarSystem(int x, int y);
	int getCentralX();
	int getCentralY();
	void drawPlanets();
	void movePlanets();
	void planetCollision(CPlayer* player);
	void playerMoveOnPlanet(CPlayer* player);
	void PlanetGravity(CPlayer* player);
	void updatePlayerStats(CPlayer* player);

private:
	CPlanet* planet[15];

	//static characteristics
	int solarSystemNumber;
	int planetsAmount;
	int solarSystemRadius;

	int colorScheme[3];

	CSDL_setup* sdl_Setup;
};

