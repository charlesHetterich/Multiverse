#include "stdafx.h"
#include "planets.h"

bool landedPlanetSwitched;

CPlanet::CPlanet(int SolarSystemNumber ,int PlanetNumber, CSDL_setup* csdl_setup, CPlanet* OriginPlanet, float OriginX, float OriginY, float Size, float Mass, float DistanceFromOrigin, float RotationSpeed, bool constantLocation, std::string filePath, int r, int g, int b)
{
	solarSystemNumber = SolarSystemNumber;
	planetNumber = PlanetNumber;
	sdl_Setup = csdl_setup;

	size = Size;
	mass = Mass;
	distanceFromOrigin = DistanceFromOrigin;
	rotationSpeed = (RotationSpeed) * (M_PI / 180);
	radians = (rand() % 200*M_PI)/100;
	staticLocation = constantLocation;

	originPlanet = OriginPlanet;
	if (originPlanet)
	{
		originX = originPlanet->planet->getX() + (originPlanet->size / 2);
		originY = originPlanet->planet->getY() + (originPlanet->size / 2);
	}

	if (originPlanet == NULL)
	{
		originX = OriginX;
		originY = OriginY;
	}

	planet = new Csprites(sdl_Setup, filePath, originX - (size / 2), originY - (size / 2), size, size, 100, 100);
	SDL_SetTextureColorMod(planet->getTexture(), r, g, b);
}


CPlanet::~CPlanet()
{
	//delete bumpSound;
	//delete planet;
	//delete originPlanet;
}

void CPlanet::drawBackground()
{
	planet->drawStatic();
}

void CPlanet::show()
{
	planet->drawReg(0, 0);
}

void CPlanet::rotate()
{
	radians += rotationSpeed;
	if (radians >= 2 * M_PI) { radians -= 2 * M_PI; }

	planet->setX((originX + (distanceFromOrigin*cos(radians))) - (size/2));
	planet->setY((originY + (distanceFromOrigin*sin(radians))) - (size/2));
}

void CPlanet::setOriginX(float newOriginX)
{
	if (newOriginX) { originX = newOriginX; planet->setX(originX - planet->getW()/2); }
	if (originPlanet) { originX = originPlanet->planet->getX() + (originPlanet->size / 2); }
}

void CPlanet::setOriginY(float newOriginY)
{
	if (originY) { originY = newOriginY; planet->setY(originY - planet->getH()/2); }
	if (originPlanet) { originY = originPlanet->planet->getY() + (originPlanet->size / 2); }
}

bool CPlanet::getMoving()
{
	return staticLocation;
}

void CPlanet::getGravity(CPlayer* player)
{
	player->playerVelocityX -= gravity * cos(playerPlanetAngle);
	player->playerVelocityY += gravity * sin(playerPlanetAngle);
}

void CPlanet::planetCollision(CPlayer* player)
{
		if (playerDistanceFromCore < player->player->getW() / 2 + size / 2)
		{
			if (hit == false && totalPlayerVelocityPrespectiveToPlanet > 10)
			{
				float newTravelAngle = 0;
				if (player->getTravelAngle() > playerPlanetAngle) { newTravelAngle = M_PI + playerPlanetAngle - (player->getTravelAngle() - playerPlanetAngle); }
				else { newTravelAngle = M_PI + playerPlanetAngle + (playerPlanetAngle - player->getTravelAngle()); }

				player->playerVelocityX = (totalPlayerVelocity * cos(newTravelAngle)) + distanceFromOrigin*rotationSpeed*-sin(radians);
				player->playerVelocityY = (totalPlayerVelocity * -sin(newTravelAngle)) + distanceFromOrigin*rotationSpeed*cos(radians);

				bumpSound->playSound(0);

				hit = true;
			}
			//landing
			else //if (totalPlayerVelocityPrespectiveToPlanet < 10)
			{
				if (!player->getTakingOff() | player->getPlanetLandedOn() != planetNumber) { player->landShip(solarSystemNumber, planetNumber, size, -playerPlanetAngle); }
			}
		}
		else { hit = false; }
}

void CPlanet::playerMoveOnPlanet(CPlayer* player)
{
	player->player->setX(planetOrgX + (size / 2 + player->player->getW() / 2)*cos(player->getLandedSpeed()) - player->player->getW() / 2);
	player->player->setY(planetOrgY + (size / 2 + player->player->getH() / 2)*sin(player->getLandedSpeed()) - player->player->getH() / 2);
	if (player->getLanded() && SDL_JoystickGetButton(player->getController(), 10) && !player->getTakingOff()) { player->takeOff(distanceFromOrigin*rotationSpeed*-sin(radians), distanceFromOrigin*rotationSpeed*cos(radians)); }
}

void CPlanet::updateStats(CPlayer* player)
{
	playerOrgX = player->player->getX() + player->player->getW() / 2;
	playerOrgY = player->player->getY() + player->player->getH() / 2;
	planetOrgX = planet->getX() + size / 2;
	planetOrgY = planet->getY() + size / 2;
	playerDistanceFromCore = sqrt(((playerOrgX - planetOrgX) * (playerOrgX - planetOrgX) + (playerOrgY - planetOrgY) * (playerOrgY - planetOrgY)));
	playerPlanetAngle = acos((playerOrgX - planetOrgX) / playerDistanceFromCore);
	if ((playerOrgY - planetOrgY) > 0) { playerPlanetAngle = -playerPlanetAngle + 2 * M_PI; }
	totalPlayerVelocity = sqrt(player->playerVelocityX*player->playerVelocityX + player->playerVelocityY*player->playerVelocityY);
	totalPlayerVelocityPrespectiveToPlanet = sqrt((player->playerVelocityX - distanceFromOrigin*rotationSpeed*-sin(radians)) * (player->playerVelocityX - distanceFromOrigin*rotationSpeed*-sin(radians)) + (player->playerVelocityY - distanceFromOrigin*rotationSpeed*cos(radians)) *  (player->playerVelocityY - distanceFromOrigin*rotationSpeed*cos(radians)));
	gravity = mass / (playerDistanceFromCore * 5);
	if (gravity < 0.1) { gravity = 0; }
}

float CPlanet::getDistanceFromOrigin()
{
	return distanceFromOrigin;
}

int CPlanet::getSize()
{
	return size;
}