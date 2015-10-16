#include "stdafx.h"
#include "SDL_setup.h"


CSDL_setup::CSDL_setup(bool* quit, int ScreenWidth, int ScreenHeight)
{
	getScreenWidth = ScreenWidth;
	getScreenHeight = ScreenHeight;
	window = NULL;
	window = SDL_CreateWindow("Planets", 200, 36, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		std::cout << "Window couldn't be created" << std::endl;
		*quit = true;
	}

	renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	mainEvent = new SDL_Event();
}


CSDL_setup::~CSDL_setup()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	delete mainEvent;
}

SDL_Renderer* CSDL_setup::GetRenderer()
{
	return renderer;
}

SDL_Event* CSDL_setup::GetMainEvent()
{
	return mainEvent;
}

void CSDL_setup::begin()
{
	SDL_PollEvent(mainEvent);
	SDL_RenderClear(renderer);
}

void CSDL_setup::end()
{
	SDL_RenderPresent(renderer);
}