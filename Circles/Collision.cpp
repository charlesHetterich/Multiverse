#include "stdafx.h"
#include "Collision.h"

CCollision::CCollision()
{
}


CCollision::~CCollision()
{
}

bool CCollision::checkCollisionState(SDL_Rect object1, SDL_Rect object2)
{
	//object1's top face collision
	collision[0] = object1.y >= object2.y + object2.h;

	//object1's bottom face collision
	collision[1] = object1.y + object1.h <= object2.y;

	//object1's left face collision
	collision[2] = object1.x <= object2.x + object2.w - 1;

	//object1's rig.ht face collision
	collision[3] = object1.x + object1.w >= object2.x + 1;


	//difines object1s position relative to object
	if (!collision[0] && collision[1] && collision[2] && collision[3]) { aboveObject = true; }
	else { aboveObject = false; }
	if (collision[0] && !collision[1] && collision[2] && collision[3]) { bellowObject = true; }
	else { bellowObject = false; }
	if (!collision[0] && !collision[1] && collision[2] && !collision[3]) { leftOfObject = true; }
	else { leftOfObject = false; }
	if (!collision[0] && !collision[1] && !collision[2] && collision[3]) { rightOfObject = true; }
	else { rightOfObject = false; }
	if (!collision[0] && collision[1] && collision[2] && !collision[3]) { aboveLeftOfObject = true; }
	else { aboveLeftOfObject = false; }
	if (!collision[0] && collision[1] && !collision[2] && collision[3]) { aboveRightOfObject = true; }
	else { aboveRightOfObject = false; }
	if (collision[0] && !collision[1] && collision[2] && !collision[3]) { bellowLeftOfObject = true; }
	else { bellowLeftOfObject = false; }
	if (collision[0] && !collision[1] && !collision[2] && collision[3]) { bellowRightOfObject = true; }
	else { bellowRightOfObject = false; }
	if (!collision[0] && !collision[1] && collision[2] && collision[3]) { hitObject = true; }
	else { hitObject = false; }

	//sets where object1 can move ([0]=up | [1]=down | [2]=left | [3]=right | [4]=hit)
	if ((bellowObject && object1.y == object2.y + object2.h) | (bellowLeftOfObject && object1.y == object2.y + object2.h && object1.x + object1.h == object2.x) | (bellowRightOfObject && object1.y == object2.y + object2.h && object1.x == object2.x + object2.h)) { collisionState[0] = false; }
	if ((aboveObject && object1.y + object1.h == object2.y) | (aboveLeftOfObject && object1.y + object1.h == object2.y && object1.x + object1.h == object2.x) | (aboveRightOfObject && object1.y + object1.h == object2.y && object1.x == object2.x + object2.h)) { collisionState[1] = false; }
	if (rightOfObject && object1.x == object2.x + object2.w) { collisionState[2] = false; }
	if (leftOfObject && object1.x + object1.w == object2.x) { collisionState[3] = false; }
	if (hitObject){ collisionState[4] = true; }

	return collisionState;
}

void CCollision::resetCollisionTruth()
{
	collisionState[0] = true;
	collisionState[1] = true;
	collisionState[2] = true;
	collisionState[3] = true;
	collisionState[4] = false;
}

bool CCollision::checkMouseCollision(int x, int y, SDL_Rect object)
{
	if (x > object.x && x < object.x + object.w && y > object.y && y < object.y + object.h)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int CCollision::distanceBetween(int pos1, int pos2)
{
	return pos2 - pos1;
}