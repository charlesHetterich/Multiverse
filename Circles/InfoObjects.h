#pragma once
#include "SDL_setup.h"
#include "sprites.h"
class CInfoObjects
{
public:
	CInfoObjects(CSDL_setup* csdl_Setup);
	~CInfoObjects();

	//miniMap
	void mapObject(int x, int y, int r, int g, int b);
	void setMapScope(int radius);
	void drawMap();

private:

	//mini map
	Csprites* miniMap;
	Csprites* miniMapObjects;
	float mapScope;
	float objectX;
	float objectY;

	CSDL_setup* sdl_Setup;
};

