#include "stdafx.h"
#include "Music.h"

Mix_Music *music[1];
Mix_Chunk *sound[2];

CMusic::CMusic()
{
	//Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	Mix_OpenAudio(88200, MIX_DEFAULT_FORMAT, 2, NULL);

	//music
	music[0] = Mix_LoadMUS("sounds/freedom.wav");

	//sound
	sound[0] = Mix_LoadWAV("sounds/bump.wav");
	sound[1] = Mix_LoadWAV("sounds/beep.wav");

	if (sound[0] == NULL)
	{
		std::cout << "music was not loaded!";
	}
}


CMusic::~CMusic()
{
	Mix_FreeMusic(music[0]);
	Mix_FreeMusic(music[1]);
	Mix_FreeMusic(music[2]);

	Mix_FreeChunk(sound[0]);
	Mix_FreeChunk(sound[1]);
	Mix_FreeChunk(sound[2]);
	Mix_FreeChunk(sound[3]);

	Mix_CloseAudio();
}

void CMusic::playMusic(int song)
{
	Mix_PlayMusic(music[song], -1);
}

void CMusic::playSound(int soundNumber)
{
	Mix_PlayChannel(-1, sound[soundNumber], 0);
}
