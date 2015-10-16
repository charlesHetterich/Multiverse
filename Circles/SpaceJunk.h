#pragma once
#include "SDL_setup.h"
#include "sprites.h"
#include "Player.h"
#include "Music.h"

class CSpaceJunk
{
public:
	CSpaceJunk(CSDL_setup* csdl_Setup, int JunkType);
	~CSpaceJunk();

	void moveJunk();
	void showJunk();

	//junk landing on planets
	void landShip(int solarSystem, int planet, int planetSize, float angle);
	void changePlanetLandedOn(int planet, int planetSize, float angle);
	void takeOff(float planetOnSpeedX, float planetOnSpeedY);
	void takeOffComplete();
	float getLandedSpeed();
	bool getLanded();
	bool getTakingOff();
	int getPlanetLandedOn();
	int getSolarSystemLandedIn();

	SDL_Joystick* getController();

private:
	//the big bang explosion
	Csprites* bigBang;

	CSDL_setup* sdl_Setup;
};

