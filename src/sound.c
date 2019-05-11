#include <stdio.h>
#include <string.h>

#include <SDL2/SDL.h>

#include "sound.h"

unsigned int sound_enabled = 1;
SDL_AudioSpec ds, os;
Uint8 sound_data[SOUND_DATA_SIZE];

void SoundInit (void) {
	if (SDL_InitSubSystem (SDL_INIT_AUDIO) < 0) {
		printf ("SoundInit(): Cannot initialize SDL audio\n");
		sound_enabled = 0;
		return;
	}
	sound_enabled = 1;
	
	ds.freq = 44100;
	ds.channels = 2;
	ds.format = AUDIO_U8;
	ds.samples = SOUND_DATA_SIZE*2;
	ds.callback = SoundPlayCallback;
	if (SDL_OpenAudio(&ds, &os) < 0) {
		printf ("SoundFilePlay(): SDL_OpenAudio() failed.\n"\
		"SDL_GetError(): %s\n", SDL_GetError());
		return;
	}
	
	memset (sound_data, '@', SOUND_DATA_SIZE);
}

void SoundPlayCallback (void *userdata, Uint8 *stream, int len) {
	snprintf ((char *)stream, len, (char *)sound_data);
}

int SoundThreadFunc (void *data) {
	SDL_PauseAudio (0);
	SDL_Delay (125);
	SDL_PauseAudio (1);
	return 0;
}

void SoundThreadStart (void) {
	SDL_Thread *thread = SDL_CreateThread (SoundThreadFunc, "thread", NULL);
	SDL_DetachThread (thread);
}
