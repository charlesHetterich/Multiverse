#include "SDL_setup.h"
#include "sprites.h"
#include "Music.h"
#include "Mouse.h"
#include "SDL_gamecontroller.h"
#pragma once
class CPlayer
{
public:
	CPlayer(CSDL_setup* csdl_Setup);
	~CPlayer();
	void movePlayer();
	void showPlayer();
	void controlPlayer();
	float getTravelAngle();

	int totalGravityX;
	int totalGravityY;

	Csprites* player;
	float playerVelocityX;
	float playerVelocityY;

	int getMass();

	//ship landing on planet stuff
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
	//rocket parts

	Csprites* engine;
	float anglePlayerFacing;

	//characteristics
	float playerMass; //tenthousands of kg

	//changing variables

	float EnginePower;
	float travelingAngle;

	bool landed;
	bool takingOff;
	float takeOffPreSpeedX;
	float takeOffPreSpeedY;
	float landedSpeed;
	float landedRocketAngle;
	float landDestinationAngle;

	int solarSystemLandedIn;
	int planetLandedOn;
	float planetLandedOnSize;

	int zoomSpeed;

	//controller
	CMouse* mouse;
	SDL_Joystick* gamePad;
	float controllerAngle;
	const int JOYSTICK_DEAD_ZONE = 8000;

	CSDL_setup* sdl_Setup;
};

