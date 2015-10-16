#include "stdafx.h"
#include "InfoObjects.h"


CInfoObjects::CInfoObjects(CSDL_setup* csdl_Setup)
{
	sdl_Setup = csdl_Setup;

	miniMap = new Csprites(sdl_Setup, "images/white_circle_small.png", sdl_Setup->getScreenWidth - 220, 20, 200, 200, 100, 100);
	miniMapObjects = new Csprites(sdl_Setup, "images/white_circle_small.png", NULL, NULL, 4, 4, 100, 100);
}


CInfoObjects::~CInfoObjects()
{
	delete miniMap;
	delete miniMapObjects;
}

//////////////////
/////MINI MAP/////
//////////////////
void CInfoObjects::drawMap()
{
	miniMap->drawStatic();
}

void CInfoObjects::setMapScope(int radius)
{
	mapScope = radius;
}

void CInfoObjects::mapObject(int x, int y, int r, int g, int b)
{
	SDL_SetTextureColorMod(miniMapObjects->getTexture(), r, g, b);
	objectX = miniMap->getX() + miniMap->getW()/2 + (x*(float)(miniMap->getW()/2/mapScope)) - miniMapObjects->getW();
	objectY = miniMap->getY() + miniMap->getH()/2 + (y*(float)(miniMap->getH()/2/mapScope)) - miniMapObjects->getH();
	miniMapObjects->setX(objectX);
	miniMapObjects->setY(objectY);
	miniMapObjects->drawStatic();
}
