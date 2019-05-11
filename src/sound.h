#ifndef SOUND_H
#define SOUND_H 1

#include <SDL2/SDL.h>

extern unsigned int sound_enabled;
extern SDL_AudioSpec ds, os;
#define SOUND_DATA_SIZE 1024
extern Uint8 sound_data[SOUND_DATA_SIZE];

void SoundInit(void);
void SoundPlayCallback(void *userdata, Uint8 *stream, int len);
int SoundThreadFunc(void *data);
void SoundThreadStart(void);

#endif /* SOUND_H */
