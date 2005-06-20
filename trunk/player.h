#include "SDL.h"
#include "SDL_thread.h"
#include "SDL_mixer.h"



void InitPlayer();
void CleanPlayer(Mix_Music *midi);

Mix_Music *LoadMidi(char *fichier);
void PlayMidi(Mix_Music *midi);
void StopMidi();
