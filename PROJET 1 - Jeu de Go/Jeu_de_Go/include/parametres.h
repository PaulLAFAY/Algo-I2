/*

    prototypes des fonctions permettant l'affichage et la gestion des parametres

*/

#ifndef DEF_PARAMETRES
#define DEF_PARAMETRES

#include "../include/constantes.h"

SDL_Surface* playParametres(SDL_Surface* surface[NB_SURFACE], Mix_Chunk* tableauSon[2], Mix_Music* musique);
void initPositionParam(SDL_Rect* positionOrigine, SDL_Rect* positionTitre, SDL_Rect positionBouton[10], SDL_Rect positionVolumes[2], SDL_Surface* surface[NB_SURFACE]);

#endif // DEF_PARAMETRES
