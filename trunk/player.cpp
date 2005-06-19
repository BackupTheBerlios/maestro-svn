#include "player.h"



/* On initialise SDL */
void InitPlayer()
{
  SDL_Init(SDL_INIT_AUDIO);
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 512);
}


/* On quitte SDL en liberant tout */
void CleanPlayer(Mix_Music *midi)
{
  Mix_FreeMusic(midi);
  Mix_CloseAudio();
  SDL_Quit();
}


/* On charge un midi en memoire */
Mix_Music *LoadMidi(char *fichier)
{
  return(Mix_LoadMUS(fichier));
}


/* On joue la musique */
void PlayMidi(Mix_Music *midi)
{
  if (!(Mix_PlayingMusic()))
    {  
      Mix_PlayMusic(midi,1);
      Mix_VolumeMusic(SDL_MIX_MAXVOLUME);
    }
}


/* On arrete la lecture du midi et on repart du debut */
void StopMidi()
{
  Mix_HaltMusic();
  Mix_RewindMusic();
}
