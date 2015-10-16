#include "stdafx.h"
#include "Player.h"


CPlayer::CPlayer(CSDL_setup* csdl_Setup)
{
	sdl_Setup = csdl_Setup;
	player = new Csprites(sdl_Setup, "images/rocket.png", -1, 450, 50, 50, 301, 301);
	engine = new Csprites(sdl_Setup, "images/engine.png", NULL, NULL, 30, 30, 301, 301);
	playerMass = 1;

	//controller
	mouse = new CMouse(sdl_Setup);
	
	SDL_Init(SDL_INIT_GAMECONTROLLER);
	if (SDL_Init(SDL_INIT_JOYSTICK) < 0)
	{
		std::cout << "no controller connected!";
	}
	gamePad = SDL_JoystickOpen(0);
	if (gamePad == NULL)
	{
		std::cout << "no controller connected";
	}
}


CPlayer::~CPlayer()
{
	SDL_JoystickClose(gamePad);
	delete player;
	delete engine;
	delete mouse;
}

void CPlayer::movePlayer()
{
	if (!landed)
	{
		player->setX(player->getX() + playerVelocityX);
		player->setY(player->getY() + playerVelocityY);
	}
}

void CPlayer::showPlayer()
{
	player->drawReg(0, 0);

	if (!landed)
	{
		engine->setX((player->getX() + player->getW() / 2) - 20 * cos(-anglePlayerFacing) - (engine->getW() / 2));
		engine->setY((player->getY() + player->getH() / 2) - 20 * sin(-anglePlayerFacing) - (engine->getW() / 2));
	}
	else
	{
		engine->setX((player->getX() + player->getW() / 2) - 20 * cos(landedRocketAngle) - (engine->getW() / 2));
		engine->setY((player->getY() + player->getH() / 2) - 20 * sin(landedRocketAngle) - (engine->getW() / 2));
	}

	engine->drawReg(0, 0);
}

void CPlayer::controlPlayer()
{
//	std::cout << SDL_GameControllerMapping(s) << "\n";
		SDL_JoystickUpdate();
	if (sqrt(SDL_JoystickGetAxis(gamePad, 1)*SDL_JoystickGetAxis(gamePad, 1) + SDL_JoystickGetAxis(gamePad, 0)*SDL_JoystickGetAxis(gamePad, 0)) > JOYSTICK_DEAD_ZONE)
	{
		if (!landed && !takingOff)
		{
			//finds direction of player
			anglePlayerFacing = -atan2((double)SDL_JoystickGetAxis(gamePad, 1), (double)SDL_JoystickGetAxis(gamePad, 0));
			if (anglePlayerFacing < 0) { anglePlayerFacing += 2 * M_PI; }

			//calculates power of engine and speed of rocket
			EnginePower = (sqrt(SDL_JoystickGetAxis(gamePad, 1)*SDL_JoystickGetAxis(gamePad, 1) + SDL_JoystickGetAxis(gamePad, 0)*SDL_JoystickGetAxis(gamePad, 0))) / 12000;
			playerVelocityX += (EnginePower)*cos(-anglePlayerFacing);
			playerVelocityY += (EnginePower)*sin(-anglePlayerFacing);
		}
		//landed on a planet
		else if (landed)
		{
			if (!SDL_JoystickGetButton(gamePad, 10)) { landedSpeed += ((SDL_JoystickGetAxis(gamePad, 1) / 5000) * (M_PI / 180)) * (player->getW()/planetLandedOnSize); }
			landedRocketAngle = landedSpeed / (player->getW()/planetLandedOnSize);
		}
	}
	////////////////////////////////////////
	////////IMPORTANT TO REMEMBER///////////
	//************************************//
	/////CONTROL FOR TAKING OFF IS IN///////
	///////PLANET FUNCTION NOT HERE/////////
	////////////////////////////////////////
	if (takingOff)
	{
		playerVelocityX += 0.1*cos(landedSpeed);
		playerVelocityY += 0.1*sin(landedSpeed);
		if (sqrt((playerVelocityX - takeOffPreSpeedX) * (playerVelocityX - takeOffPreSpeedX) + (playerVelocityY - takeOffPreSpeedY) * (playerVelocityY - takeOffPreSpeedY)) > 8) { takeOffComplete(); }
	}
	if (SDL_JoystickGetButton(gamePad, 9)) { player->setZoom(player->getZoom() - 1); }
	if (SDL_JoystickGetButton(gamePad, 8)) { player->setZoom(player->getZoom() + 1); }
}

int CPlayer::getMass()
{
	return playerMass;
}

float CPlayer::getTravelAngle()
{
	travelingAngle = atan(-playerVelocityY / playerVelocityX);
	if (playerVelocityX > 0 && playerVelocityY < 0) { travelingAngle = fabs(travelingAngle); }
	else if (playerVelocityX < 0 && playerVelocityY < 0) { travelingAngle = M_PI - fabs(travelingAngle); }
	else if (playerVelocityX < 0 && playerVelocityY > 0) { travelingAngle = M_PI + fabs(travelingAngle); }
	else if (playerVelocityX > 0 && playerVelocityY > 0) { travelingAngle = 2*M_PI - fabs(travelingAngle); }
	return travelingAngle;
}

void CPlayer::landShip(int solarSystem, int planet, int planetSize, float angle)
{
	landed = true;
	takingOff = false;
	landedRocketAngle = -anglePlayerFacing;
	solarSystemLandedIn = solarSystem;
	planetLandedOn = planet;
	planetLandedOnSize = planetSize;
	playerVelocityX = 0;
	playerVelocityY = 0;
	player->setZoomSpeed(4, 0.1);
	landedSpeed = angle;
}

void CPlayer::changePlanetLandedOn(int planet, int planetSize, float angle)
{
	planetLandedOn = planet;
	planetLandedOnSize = planetSize;
	landedSpeed = angle;
}

void CPlayer::takeOff(float planetOnSpeedX, float planetOnSpeedY)
{
	landed = false;
	takingOff = true;
	player->setZoomSpeed(-4, 0.1);
	anglePlayerFacing = -landedRocketAngle;
	takeOffPreSpeedX = planetOnSpeedX;
	takeOffPreSpeedY = planetOnSpeedY;
	playerVelocityX = takeOffPreSpeedX;
	playerVelocityY = takeOffPreSpeedY;
}

void CPlayer::takeOffComplete()
{
	takingOff = false;
	planetLandedOn = -1;
}

float CPlayer::getLandedSpeed()
{
	return landedSpeed;
}

bool CPlayer::getLanded()
{
	return landed;
}

bool CPlayer::getTakingOff()
{
	return takingOff;
}

int CPlayer::getSolarSystemLandedIn()
{
	return solarSystemLandedIn;
}

int CPlayer::getPlanetLandedOn()
{
	return planetLandedOn;
}

SDL_Joystick* CPlayer::getController()
{
	return gamePad;
}