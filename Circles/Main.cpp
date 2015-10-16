#include "stdafx.h"
#include "Game.h"

int main(int argc, char *argv[])
{
	CGame* game = new CGame();

	game->gameLoop();

	//delete game;
	game->saveGame();
	
	return 0;
}

