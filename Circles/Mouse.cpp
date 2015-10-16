#include "stdafx.h"
#include "Mouse.h"


CMouse::CMouse(CSDL_setup* csdl_setup)
{	
	sdl_setup = csdl_setup;
}


CMouse::~CMouse()
{
}

bool CMouse::mouseLeftClick()
{
	switch (sdl_setup->GetMainEvent()->type)
	{
	case SDL_MOUSEBUTTONDOWN:
		switch (sdl_setup->GetMainEvent()->button.button)
		{
		case SDL_BUTTON_LEFT:
			return true;
			break;
		}
		break;

	case SDL_MOUSEBUTTONUP:
	{
		switch (sdl_setup->GetMainEvent()->button.button)
		{
			case SDL_BUTTON_LEFT:
				
			break;
		}
	}

	default:
		break;
	}
	return false;
}

void CMouse::setMousePosition()
{
	SDL_GetMouseState(&mouseX, &mouseY);
}

int CMouse::getMouseX()
{
	return mouseX;
}

int CMouse::getMouseY()
{
	return mouseY;
}