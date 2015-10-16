#include "stdafx.h"
#include "Text.h"


CText::CText(CSDL_setup* csdl_Setup)
{
	sdl_Setup = csdl_Setup;
	TTF_Init();

	Color3 = { 255, 255, 255 };
	font = TTF_OpenFont("font/timeburner.ttf", 30);
}

CText::~CText()
{
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);
	TTF_Quit();
}

void CText::write(std::string Font, int size, std::string Text, int x, int y, int w, int h, int imageY)
{
	TTF_Init();
	rect.x = x;
	rect.y = y;

	crop.x = 0;
	crop.y = imageY;

	if (fontFile != Font | fontSize != size)
	{
		fontFile = Font;
		fontSize = size;
		font = TTF_OpenFont(fontFile.c_str(), fontSize);
	}

	//render the message to an SDL_Surface, as that's what ttf_renderText_x returns
	if (text != Text)
	{
		if (surf) { SDL_FreeSurface(surf); }
		if (texture) { SDL_DestroyTexture(texture); }
		text = Text;
		surf = TTF_RenderText_Blended_Wrapped(font, text.c_str(), Color3, w);



		texture = SDL_CreateTextureFromSurface(sdl_Setup->GetRenderer(), surf);
	}

	if (h != NULL)
	{
		crop.w = w;
		rect.w = w;
		if (crop.h + crop.y < surf->h && crop.y >= 0) { rect.h = h; 	crop.h = h; }
		else if (crop.h + crop.y > surf->h) { rect.h = h - (crop.h + crop.y - surf->h); }
		if (crop.y < 0) { rect.h = h + crop.y; rect.y = y - crop.y; }
	}
	else
	{
		crop.w = surf->w;
		crop.h = surf->h;
		rect.w = surf->w;
		rect.h = surf->h;
	}

	SDL_RenderCopy(sdl_Setup->GetRenderer(), texture, &crop, &rect);
}