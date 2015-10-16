#include "stdafx.h"
#include "SolarSystem.h"


CSolarSystem::CSolarSystem(int SolarSystemNumber, CSDL_setup* csdl_Setup, int PlanetsAmount)
{
	sdl_Setup = csdl_Setup;
	solarSystemNumber = SolarSystemNumber;
	planetsAmount = PlanetsAmount;

	float sunSize = (rand() % 2000 + 3000);
	float sunMass = (rand() % 6000 + 1000);
	planet[0] = new CPlanet(solarSystemNumber, 0, sdl_Setup, NULL, 1, 1, sunSize, sunMass,	NULL, NULL, true, "images/white_circle_small.png", rand(), rand(), rand());


	for (int currentPlanet = 1; currentPlanet < planetsAmount; currentPlanet++)
	{
		float planetSize = (rand() % 1000 + 100);
		float planetMass = (rand() % 500 + 500);
		float distanceFromOrigin = (rand() % 1000) + (planet[currentPlanet - 1]->getDistanceFromOrigin() + planet[currentPlanet - 1]->getSize() / 2 + planetSize / 2 + 300);
		planet[currentPlanet] = new CPlanet(solarSystemNumber, currentPlanet, sdl_Setup, planet[0], NULL, NULL, planetSize, planetMass, distanceFromOrigin, ((rand() % 95 + 5)*0.01)/(distanceFromOrigin*0.001) , false, "images/white_circle_small.png", rand(), rand(), rand());
	}
	solarSystemRadius = planet[planetsAmount - 1]->getDistanceFromOrigin() + planet[planetsAmount - 1]->getSize() / 2;
}

CSolarSystem::~CSolarSystem()
{
	delete planet;
}

void CSolarSystem::placeSolarSystem(int x, int y)
{
	planet[0]->setOriginX(x);
	planet[0]->setOriginY(y);
}

int CSolarSystem::getCentralX()
{
	return planet[0]->planet->getX() + planet[0]->getSize() / 2;
}

int CSolarSystem::getCentralY()
{
	return planet[0]->planet->getY() + planet[0]->getSize() / 2;
}

void CSolarSystem::drawPlanets()
{
	for (int currentPlanet = 0; currentPlanet < planetsAmount; currentPlanet++)
	{
		planet[currentPlanet]->planet->drawReg(0,0);
	}
}

void CSolarSystem::movePlanets()
{
	for (int currentPlanet = 0; currentPlanet < planetsAmount; currentPlanet++)
	{
		if (!planet[currentPlanet]->getMoving()) 
		{
			planet[currentPlanet]->setOriginX(NULL);
			planet[currentPlanet]->setOriginY(NULL);
			planet[currentPlanet]->rotate(); 
		}
	}
}

void CSolarSystem::planetCollision(CPlayer* player)
{
	for (int currentPlanet = 0; currentPlanet < planetsAmount; currentPlanet++)
	{
		if (!player->getLanded())
		{
			planet[currentPlanet]->planetCollision(player);
		}
	}
}

void CSolarSystem::playerMoveOnPlanet(CPlayer* player)
{
	for (int currentPlanet = 0; currentPlanet < planetsAmount; currentPlanet++)
	{
		if (player->getLanded() && player->getSolarSystemLandedIn() == solarSystemNumber)
		{ 
			planet[player->getPlanetLandedOn()]->playerMoveOnPlanet(player); 
		}
	}
}

void CSolarSystem::PlanetGravity(CPlayer* player)
{
	for (int currentPlanet = 0; currentPlanet < planetsAmount; currentPlanet++)
	{
		if (!player->getLanded() && !player->getTakingOff())
		{
			planet[currentPlanet]->getGravity(player);
		}
	}
}

void CSolarSystem::updatePlayerStats(CPlayer* player)
{
	for (int currentPlanet = 0; currentPlanet < planetsAmount; currentPlanet++)
	{
		planet[currentPlanet]->updateStats(player);
	}
}

int CSolarSystem::getSolarSystemRadius()
{
	return solarSystemRadius;
}
