#pragma once
#include "SDL_setup.h"
#include "sprites.h"
#include "Collision.h"
#include "Player.h"
class CPlanet
{
public:
	CPlanet(int SolarSystemNumber, int PlanetNumber, CSDL_setup* csdl_setup, CPlanet* OriginPlanet, float OriginX, float OriginY, float Size, float Mass, float DistanceFromOrigin, float RotationSpeed, bool constantLocation, std::string filePath, int r, int g, int b);
	~CPlanet();

	void rotate();
	void show();
	void drawBackground();
	void setOriginY(float newOriginY);
	void setOriginX(float newOriginX);
	bool getMoving();
	void getGravity(CPlayer* player);
	void planetCollision(CPlayer* player);
	void updateStats(CPlayer* player);
	void playerMoveOnPlanet(CPlayer* player);
	float getDistanceFromOrigin();
	int getSize();

	Csprites* planet;
private:

	//planet characteristics
	int planetNumber;
	int solarSystemNumber;
	float size;
	float mass;
	float distanceFromOrigin;
	float rotationSpeed;
	bool staticLocation;
	float originX;
	float originY;
	CPlanet* originPlanet;

	//changing stats
	double playerOrgX;
	double playerOrgY;
	double planetOrgX;
	double planetOrgY;
	double playerDistanceFromCore;
	double playerPlanetAngle;
	double totalPlayerVelocity;
	double totalPlayerVelocityPrespectiveToPlanet;
	bool hit;
	float gravity;

	float radians;

	CMusic* bumpSound;
	CSDL_setup* sdl_Setup;
};