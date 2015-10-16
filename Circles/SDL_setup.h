#pragma once;
class CSDL_setup
{
public:
	CSDL_setup(bool* quit, int ScreenWidth, int ScreenHeight);
	~CSDL_setup();
	
	SDL_Renderer* GetRenderer();
	SDL_Event* GetMainEvent();

	void begin();
	void end();
	SDL_Event* mainEvent;

	int getScreenWidth;
	int getScreenHeight;
private:

	SDL_Window* window;
	SDL_Renderer* renderer;
};