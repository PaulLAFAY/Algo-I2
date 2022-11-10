/*

    prototype des fonctions generales du programme

*/

#ifndef DEF_GENERAL
#define DEF_GENERAL

#include "../include/constantes.h"

SDL_Surface* initSDL(SDL_Surface* surface);
void initSurface(SDL_Surface* surface[NB_SURFACE]);

void initMIXER();
Mix_Music* initMusic(Mix_Music* musique);
void initSound(Mix_Chunk* tableauSon[2]);

void quitApp(SDL_Surface* surface[NB_SURFACE], Mix_Chunk* tableauSon[2], Mix_Music* musique);

int limitFPS(int tempsPrecedent);

#endif // DEF_GENERAL
