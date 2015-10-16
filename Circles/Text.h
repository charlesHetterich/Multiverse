#pragma once
#include "SDL_setup.h"

class CText
{
public:
	CText(CSDL_setup* csdl_Setup);
	~CText();
	void write(std::string Font, int size, std::string text, int x, int y, int w, int h, int imageY);

private:

	SDL_Texture *texture;
	SDL_Surface *surf;

	SDL_Rect rect;
	SDL_Rect crop;

	SDL_Color Color3;
	TTF_Font *font;

	std::string fontFile;
	int fontSize;
	std::string text;

	CSDL_setup* sdl_Setup;
};

