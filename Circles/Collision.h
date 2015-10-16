#pragma once

//not class stuff


class CCollision
{
public:
	CCollision();
	~CCollision();
	bool checkCollisionState(SDL_Rect object1, SDL_Rect object2);
	bool checkMouseCollision(int x, int y, SDL_Rect object);
	int distanceBetween(int pos1 , int pos2);

	bool collisionState[5]; //Object1: [0]=top [1]=bottom [2]=left [3]=right [4]=hit

	void resetCollisionTruth();

private:
	bool collision[4];

	bool aboveObject;
	bool bellowObject;
	bool leftOfObject;
	bool rightOfObject;
	bool aboveLeftOfObject;
	bool aboveRightOfObject;
	bool bellowLeftOfObject;
	bool bellowRightOfObject;
	bool hitObject;


};

