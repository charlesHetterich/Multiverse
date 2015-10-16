#pragma once
#include "SDL_setup.h"
class CMouse
{
public:
	CMouse(CSDL_setup* csdl_setup);
	~CMouse();
	bool mouseLeftClick();
	void setMousePosition();
	int getMouseX();
	int getMouseY();

private:
	CSDL_setup* sdl_setup;

	int mouseX;
	int mouseY;
};

